/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:13 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 21:48:37 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static bool	check_range(double num, double range_min, double range_max,
	t_parsing *p)
{
	if (num > range_max || num < range_min))
	{
		p->parsing_err = OUT_OF_RANGE_ERR;
		return (true);
	}
	return (false);
}

bool	get_float(float *dst, float range_min, float range_max, t_parsing *p)
{
	bool	sgn;

	sgn = (p->buff[p->i] == '-');
	p->i += sgn;
	if (refresh_buffer(p))
		return (true);
	*dst = 0;
	while (!p->parsing_over && p->buff[p->i] >= '0' && p->buff[p->i] <= '9')
	{
		*dst = *dst * 10.0 + p->buff[p->i] - '0';
		if (check_range(*dst * (-2.0 * sgn + 1.0), range_min, range_max, p))
			return (true);
		p->i++;
	}
	if (get_decimal(dst, range_min, range_max))
}
