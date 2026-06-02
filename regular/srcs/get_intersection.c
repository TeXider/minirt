/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/02 11:35:02 by almighty         ###   ########.fr       */
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

bool	get_sphere_intersection(t_sphere *sp, t_ray *r, float *res)
{
	t_vector	oo;
	float		roo;
	float		d;

	oo = vector_sub(&r->o, &sp->o);
	roo = vector_dot_prod(&oo, &r->n);
	d = 4 * roo * roo - 4 * (vector_square(&oo) - sp->r * sp->r);
	if (d < 0)
		return (false);
	d = sqrt(d);
	roo *= -2;
	if (roo < -d)
		return (false);
	if (roo >= d && roo - d < roo + d)
		*res = (roo - d) / 2;
	else
		*res = (roo + d) / 2;
	return (true);
}

// bool	get_cylinder_intersection(t_cylinder *cy, t_ray *r, float *res)
// {
// 	t_vector	oo;
// 	float		nr;
// 	float		noo;
// 	float		d;

// 	oo = vector_sub(&r->o, &cy->o);
// 	nr = vector_dot_prod(&r->n, &cy->n);
// 	noo = vector_dot_prod(&cy->n, &oo);
// 	d = 4 * pow(vector_dot_prod(&r->n, &oo) - nr * noo, 2) - 4 * (1 - nr * nr)
// 		* (vector_square(&oo) + noo * noo - cy->r * cy->r);
// 	if (d < 0)
// 		return (false);
// 	d = sqrt(d);
// 	nr *= -2;
// 	if (nr < -d)
// 		return (false);
// 	if (nr >= d && nr - d < nr + d)
// 		*res = (nr - d) / 2;
// 	else
// 		*res = (nr + d) / 2;
// 	return (true);
// }
