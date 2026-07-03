/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/30 10:48:57 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

bool	get_plane_intersection(t_plane *pl, t_ray *r, t_intersection *dst)
{
	float	tmp;

	tmp = vector_dot_prod(r->n, pl->n);
	if (!tmp)
		return (false);
	dst->distance = -vector_dot_prod(pl->n, vector_sub(r->o, pl->o)) / tmp;
	if (dst->distance < 0)
		return (false);
	dst->type = TPLANE;
	dst->shape = pl;
	dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
	dst->surf_n = pl->n;
	dst->color = pl->color;
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
		dst->type = TSPHERE;
		dst->shape = sp;
		dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
		dst->surf_n = vector_scale(vector_sub(dst->p, sp->o), 1.0f / sp->r);
		dst->color = sp->color;
		return (true);
	}
	return (false);
}

static inline t_vector	cylinder_surf_n(t_intersection *inter, t_cylinder *cy)
{
	return (vector_normalize(vector_sub(vector_sub(inter->p, cy->o),
				vector_scale(cy->n, vector_dot_prod(cy->n,
						vector_sub(inter->p, cy->o))))));
}

static inline bool	get_cylinder_top_intersection(t_cylinder *cy, t_ray *r,
	t_intersection *dst)
{
	t_vector	top_o;
	float		n_dot_r;
	t_vector	p;

	n_dot_r = vector_dot_prod(r->n, cy->n);
	if (!n_dot_r)
		return (false);
	top_o = vector_add(cy->o, vector_scale(cy->n, -sign(n_dot_r) * cy->h));
	dst->distance = -vector_dot_prod(cy->n, vector_sub(r->o, top_o)) / n_dot_r;
	if (dst->distance < 0)
		return (false);
	p = vector_add(vector_scale(r->n, dst->distance), r->o);
	if (vector_square(vector_sub(p, top_o)) <= cy->r * cy->r)
	{
		dst->type = TCYLINDER;
		dst->shape = cy;
		dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
		dst->surf_n = cy->n;
		dst->color = cy->color;
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

	if (get_cylinder_top_intersection(cy, r, dst))
		return (true);
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
		dst->type = TCYLINDER;
		dst->shape = cy;
		dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
		dst->surf_n = cylinder_surf_n(dst, cy);
		dst->color = cy->color;
		return (true);
	}
	return (false);
}
