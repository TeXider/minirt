/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_top_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:10:39 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 13:12:48 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_math.h"

static inline bool	get_cylinder_top_up_intersection(t_cylinder *cy, t_ray *r,
	t_intersection *dst)
{
	t_vector	top_o;
	float		n_dot_r;
	t_vector	p;

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
		dst->type = TCYLINDER;
		dst->shape = cy;
		dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
		dst->surf_n = cy->n;
		dst->color = cy->color;
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
		dst->type = TCYLINDER;
		dst->shape = cy;
		dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
		dst->surf_n = cy->n;
		dst->color = cy->color;
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
