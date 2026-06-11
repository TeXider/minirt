/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:13 by almighty          #+#    #+#             */
/*   Updated: 2026/06/08 22:46:39 by almighty         ###   ########.fr       */
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

static bool	get_mantissa(float *dst, float range_min, float range_max,
		t_parsing *p)
{
	float	mantissa;

	if (p->file[p->buff_i] != '.')
		return (false);
	mantissa = 0;
	while (!p->parsing_over && p->file[p->buff_i] >= '0' && p->file[p->buff_i] <= '9')
	{
		mantissa = *dst * 10.0 + p->file[p->buff_i] - '0';
		if (check_range(*dst, range_min, range_max, p)
			|| move_in_buff(1, p))
			return (true);
		p->buff_i++;
	}
}

bool	get_float(float *dst, float range_min, float range_max, t_parsing *p)
{
	bool	sgn;
	int		start_i;

	sgn = (p->file[p->buff_i] == '-');
	start_i = p->buff_i;
	*dst = 0;
	while (!p->parsing_over && p->file[p->buff_i] >= '0' && p->file[p->buff_i] <= '9')
	{
		*dst = *dst * 10.0 + p->file[p->buff_i++] - '0';
		if (check_range(*dst * (-2.0 * sgn + 1.0), range_min, range_max, p)
			|| move_in_buff(1, p))
			return (true);
	}
	*dst *= -2.0 * sgn + 1.0;
	if (!is_end_of_field(p) && get_mantissa(dst, range_min, range_max, p))
		return (true);
	if (start_i == p->buff_i || (!is_end_of_field(p)
		&& !(p->file[p->buff_i] == ',' && p->comma_expected)))
	{
		p->parsing_err = INVALID_FIELD_ERR;
		return (true);
	}
	return (false);
}
