/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/29 16:34:33 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/shapes.h"

bool	get_plane_intersection(t_plane *pl, t_ray *r, t_vector *res)
{
	t_vector	tmp;
	float		t;

	if (!vector_dot_product(&r->n, &pl->n))
		return (false);
	t = -vector_dot_product(&r->o, &pl->n)
		/ vector_dot_product(&r->n, &pl->n);
	*res = point_on_ray(r, t);
	return (true);
}

bool	get_sphere_intersection(t_sphere *sp, t_ray *r,
	t_vector *res)
{
	t_vector	tmp_sub;
	float		tmp_dot;
	float		d;

	tmp_sub = vector_substract(&r->o, &sp->o);
	tmp_dot = vector_dot_product(&tmp_sub, &r->n);
	d = 4 * tmp_dot * tmp_dot - 4 * (vector_square(&tmp_sub) - sp->r * sp->r);
	if (d < 1e-4f)
		return (false);
	d = sqrt(d);
	tmp_dot *= -2;
	if (tmp_dot < -d)
		return (false);
	if (tmp_dot >= d && tmp_dot - d < tmp_dot + d)
		*res = point_on_ray(r, (tmp_dot - d) / 2);
	else
		*res = point_on_ray(r, (tmp_dot + d) / 2);
	return (true);
}
