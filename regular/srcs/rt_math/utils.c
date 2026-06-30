/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pol_coef.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:32:58 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 10:44:51 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

inline bool	solve_pol_coef(t_pol_coef *pc, float *res)
{
	float	d;

	d = pc->b * pc->b - 4.0f * pc->a * pc->c;
	if (d < 0)
		return (false);
	d = sqrtf(d);
	if (-pc->b < -d)
		return (false);
	*res = (-pc->b + d * (1 - 2 * (-pc->b >= d))) / (2.0f * pc->a);
	return (true);
}

inline t_vector	point_on_ray(t_ray *r, float t)
{
	return (vector_add(r->o, vector_scale(r->n, t)));
}
