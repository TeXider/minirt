/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:13 by almighty          #+#    #+#             */
/*   Updated: 2026/06/11 20:06:31 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static bool	check_range(double num, double range_min, double range_max,
	t_parsing *p)
{
	if (num < range_min || num > range_max)
	{
		p->parsing_err = OUT_OF_RANGE_ERR;
		return (true);
	}
	return (false);
}

static bool	get_mantissa(float *dst, float range[2], t_parsing *p)
{
	float	mantissa;
	float	dec;

	if (p->line[p->line_i] != '.')
		return (false);
	p->line_i++;
	dec = 0.1;
	mantissa = 0.0;
	while (p->line[p->line_i] >= '0' && p->line[p->line_i] <= '9')
	{
		mantissa += dec * (p->line[p->line_i] - '0');
		dec /= 10.0;
		p->line_i++;
	}
	*dst += mantissa * (1.0 - 2.0 * ((*((int *)(dst)) & (1 << 31)) != 0));
	return (check_range(*dst, range[MIN], range[MAX], p));
}

bool	get_float(float *dst, float range[2], bool comma_expected, t_parsing *p)
{
	bool	sgn;
	size_t	start_i;

	sgn = (p->line[p->line_i] == '-');
	p->line_i += (sgn || p->line[p->line_i] == '+');
	start_i = p->line_i;
	*dst = 0;
	while (p->line[p->line_i] >= '0' && p->line_i <= '9')
	{
		*dst = *dst * 10.0 + p->line[p->line_i] - '0';
		if (check_range(*dst * (1.0 - 2.0 * sgn), range[MIN], range[MAX], p))
			return (true);
		p->line_i++;
	}
	*((int *)(dst)) |= (sgn << 31);
	if (!is_end_of_field(p) && get_mantissa(dst, range, p))
		return (true);
	if (start_i == p->line_i || (!is_end_of_field(p)
			&& !(p->line[p->line_i] == ',' && comma_expected)))
	{
		p->parsing_err = INVALID_FIELD_ERR;
		return (true);
	}
	p->line_i += comma_expected;
	return (false);
}

bool	get_int(int *dst, int range[2], bool comma_expected, t_parsing *p)
{
	bool	sgn;

	sgn = (p->line[p->line_i] == '-');
	p->line_i += (sgn || p->line[p->line_i] == '+');
	if (is_end_of_field(p))
	{
		p->parsing_err = INVALID_FIELD_ERR;
		return (true);
	}
	*dst = 0;
	while (p->line[p->line_i] >= '0' && p->line_i <= '9')
	{
		*dst = *dst * 10 + p->line[p->line_i] - '0';
		if (check_range(*dst * (1 - 2 * sgn), range[MIN], range[MAX], p))
			return (true);
		p->line_i++;
	}
	if (!is_end_of_field(p) && !(p->line[p->line_i] == ',' && comma_expected))
	{
		p->parsing_err = INVALID_FIELD_ERR;
		return (true);
	}
	*dst *= (1 - 2 * sgn);
	p->line_i += comma_expected;
	return (false);
}
