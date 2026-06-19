/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/19 11:52:09 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

bool	get_plane_intersection(t_plane *pl, t_ray *r, float *res)
{
	float	tmp;

	tmp = vector_dot_prod(r->n, pl->n);
	if (!tmp)
		return (false);
	*res = -vector_dot_prod(pl->n, vector_sub(r->o, pl->o)) / tmp;
	return (true);
}

bool	get_sphere_intersection(t_sphere *sp, t_ray *r, float *res)
{
	t_vector	o_diff;
	t_pol_coef	pc;
	float		d;

	o_diff = vector_sub(r->o, sp->o);
	pc = (t_pol_coef){1, 2.0f * vector_dot_prod(r->n, o_diff),
		vector_square(o_diff) - sp->r * sp->r};
	d = pc.b * pc.b - 4.0f * pc.c;
	if (d < 0)
		return (false);
	d = sqrt(d);
	if (-pc.b < -d)
		return (false);
	*res = (-pc.b + d * ((-pc.b < d) - 2 * (-pc.b >= d))) / 2.0f;
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
