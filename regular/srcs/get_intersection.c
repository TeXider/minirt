/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/30 11:45:49 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/shapes.h"

bool	get_plane_intersection(t_plane *pl, t_ray *r, float *res)
{
	t_vector	tmp;

	if (!vector_dot_prod(&r->n, &pl->n))
		return (false);
	tmp = vector_sub(&r->o, &pl->o);
	*res = -vector_dot_prod(&pl->n, &tmp)
		/ vector_dot_prod(&pl->n, &r->n);
	return (true);
}

bool	get_sphere_intersection(t_sphere *sp, t_ray *r,
	float *res)
{
	t_vector	tmp_sub;
	float		tmp_dot;
	float		d;

	tmp_sub = vector_sub(&r->o, &sp->o);
	tmp_dot = vector_dot_prod(&tmp_sub, &r->n);
	d = 4 * tmp_dot * tmp_dot - 4 * (vector_square(&tmp_sub) - sp->r * sp->r);
	if (d < 0)
		return (false);
	d = sqrt(d);
	tmp_dot *= -2;
	if (tmp_dot < -d)
		return (false);
	if (tmp_dot >= d && tmp_dot - d < tmp_dot + d)
		*res = (tmp_dot - d) / 2;
	else
		*res = (tmp_dot + d) / 2;
	return (true);
}
