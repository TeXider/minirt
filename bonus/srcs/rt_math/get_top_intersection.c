/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_top_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 01:45:18 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 01:52:15 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_math.h"

static inline bool	get_cylinder_top_up_intersection(t_cylinder *cy, t_ray *r,
	t_intersection *dst)
{
	t_vector	top_o;
	float		n_dot_r;
	t_vector	p;
	t_top		top;

	n_dot_r = vector_dot_prod(r->n, cy->n);
	if (!n_dot_r)
		return (false);
	top_o = vector_add(cy->o, vector_scale(cy->n, cy->h));
	dst->distance = -vector_dot_prod(cy->n, vector_sub(r->o, top_o)) / n_dot_r;
	if (dst->distance < 0)
		return (false);
	p = vector_add(vector_scale(r->n, dst->distance), r->o);
	if (vector_square(vector_sub(p, top_o)) <= cy->r * cy->r)
	{
		top = (t_top){top_o, cy->n, cy->e_y, cy->e_z, cy->r, cy,
			2 * cy->r + cy->h, cy->check, &cy->bump, &cy->txt, cy->color};
		set_top_inter_vals(&top, cy->h + cy->r, r, dst);
		return (true);
	}
	return (false);
}

static inline bool	get_cylinder_top_down_intersection(t_cylinder *cy, t_ray *r,
	t_intersection *dst)
{
	t_vector	top_o;
	float		n_dot_r;
	t_vector	p;
	t_top		top;

	n_dot_r = vector_dot_prod(r->n, cy->n);
	if (!n_dot_r)
		return (false);
	top_o = vector_add(cy->o, vector_scale(cy->n, -cy->h));
	dst->distance = -vector_dot_prod(cy->n, vector_sub(r->o, top_o)) / n_dot_r;
	if (dst->distance < 0)
		return (false);
	p = vector_add(vector_scale(r->n, dst->distance), r->o);
	if (vector_square(vector_sub(p, top_o)) <= cy->r * cy->r)
	{
		top = (t_top){top_o, cy->n, cy->e_y, cy->e_z, cy->r, cy,
			2 * cy->r + cy->h, cy->check, &cy->bump, &cy->txt, cy->color};
		set_top_inter_vals(&top, cy->h + cy->r, r, dst);
		return (true);
	}
	return (false);
}

bool	get_cylinder_top_intersection(t_cylinder *cy, t_ray *r,
	t_intersection *dst)
{
	t_intersection	inter;

	if (!get_cylinder_top_up_intersection(cy, r, dst))
		return (get_cylinder_top_down_intersection(cy, r, dst));
	if (!get_cylinder_top_down_intersection(cy, r, &inter))
		return (true);
	if (dst->distance > inter.distance)
		*dst = inter;
	return (true);
}

bool	get_cone_top_intersection(t_cone *co, t_ray *r, float n_dot_r,
	t_intersection *dst)
{
	t_vector	top_o;
	t_vector	p;
	t_top		top;

	if (!n_dot_r)
		return (false);
	top_o = vector_add(co->o, vector_scale(co->n, co->h));
	dst->distance = -vector_dot_prod(co->n, vector_sub(r->o, top_o)) / n_dot_r;
	if (dst->distance < 0)
		return (false);
	p = point_on_ray(r, dst->distance);
	if (vector_square(vector_sub(p, top_o)) <= co->tan_a * co->tan_a * co->h
		* co->h)
	{
		top = (t_top){top_o, co->n, co->e_y, co->e_z, co->tan_a * co->h, co,
			co->tan_a * co->h + co->h, co->check, &co->bump, &co->txt,
			co->color};
		set_top_inter_vals(&top, co->h, r, dst);
		return (true);
	}
	return (false);
}
