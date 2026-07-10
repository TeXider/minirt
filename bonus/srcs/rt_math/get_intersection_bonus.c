/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/10 08:31:38 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env_bonus.h"

bool	get_plane_intersection(t_plane *pl, t_ray *r, t_intersection *dst)
{
	float	tmp;

	tmp = vector_dot_prod(r->n, pl->n);
	if (!tmp)
		return (false);
	dst->distance = -vector_dot_prod(pl->n, vector_sub(r->o, pl->o)) / tmp;
	if (dst->distance < 0)
		return (false);
	set_plane_inter_vals(pl, r, dst);
	return (true);
}

bool	get_sphere_intersection(t_sphere *sp, t_ray *r, t_intersection *dst)
{
	t_vector	o_diff;
	t_pol_coef	pc;

	o_diff = vector_sub(r->o, sp->o);
	pc.a = 1;
	pc.b = 2.0f * vector_dot_prod(r->n, o_diff);
	pc.c = vector_square(o_diff) - sp->r * sp->r;
	if (solve_pol_coef(&pc, &dst->distance))
	{
		set_sphere_inter_vals(sp, r, dst);
		return (true);
	}
	return (false);
}

bool	get_cylinder_intersection(t_cylinder *cy, t_ray *r, t_intersection *dst)
{
	t_vector	o_diff;
	float		n_dot_r;
	float		n_dot_o_diff;
	t_pol_coef	pc;

	o_diff = vector_sub(r->o, cy->o);
	n_dot_r = vector_dot_prod(cy->n, r->n);
	n_dot_o_diff = vector_dot_prod(cy->n, o_diff);
	pc.a = 1.0f - n_dot_r * n_dot_r;
	pc.b = 2.0f * (vector_dot_prod(r->n, o_diff) - n_dot_r * n_dot_o_diff);
	pc.c = vector_square(o_diff) - n_dot_o_diff * n_dot_o_diff - cy->r * cy->r;
	if (solve_pol_coef(&pc, &dst->distance)
		&& fabs(vector_dot_prod(vector_sub(point_on_ray(r, dst->distance),
					cy->o), cy->n)) < cy->h)
	{
		set_cylinder_inter_vals(cy, r, dst);
		return (true);
	}
	return (get_cylinder_top_intersection(cy, r, dst));
}

static bool	check_solution_height(t_ray *r, t_cone *co, t_intersection *inter)
{
	float	h;

	h = vector_dot_prod(vector_sub(point_on_ray(r, inter->distance), co->o),
			co->n);
	return (0 < h && h < co->h);
}

bool	get_cone_intersection(t_cone *co, t_ray *r, t_intersection *dst)
{
	t_vector	o_diff;
	float		n_dot_r;
	float		n_dot_od;
	t_pol_coef	pc;

	n_dot_r = vector_dot_prod(r->n, co->n);
	o_diff = vector_sub(r->o, co->o);
	n_dot_od = vector_dot_prod(co->n, o_diff);
	pc.a = 1.0f - co->inter_k * n_dot_r * n_dot_r;
	pc.b = 2.0f * (vector_dot_prod(o_diff, r->n) - co->inter_k * n_dot_r
			* n_dot_od);
	pc.c = vector_square(o_diff) - co->inter_k * n_dot_od * n_dot_od;
	if (solve_pol_coef(&pc, &dst->distance)
		&& check_solution_height(r, co, dst))
	{
		set_cone_inter_vals(co, r, dst);
		return (true);
	}
	return (get_cone_top_intersection(co, r, n_dot_r, dst));
}
