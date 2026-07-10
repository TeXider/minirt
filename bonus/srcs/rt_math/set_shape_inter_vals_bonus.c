/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shape_inter_vals_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:15:56 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:31:57 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/rt_math_bonus.h"

void	set_plane_inter_vals(t_plane *pl, t_ray *r, t_intersection *dst)
{
	dst->shape = pl;
	dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
	dst->x_img_comp = vector_dot_prod(vector_sub(dst->p, pl->o), pl->e_z)
		/ pl->check;
	dst->y_img_comp = vector_dot_prod(vector_sub(dst->p, pl->o), pl->e_y)
		/ pl->check;
	dst->color = plane_color(pl, dst);
	dst->x_img_comp = fmodf(dst->x_img_comp, 1);
	dst->y_img_comp = fmodf(dst->y_img_comp, 1);
	dst->x_img_comp += (dst->x_img_comp < 0);
	dst->y_img_comp += (dst->y_img_comp < 0);
	dst->surf_n = plane_surf_n(pl, dst);
}

void	set_sphere_inter_vals(t_sphere *sp, t_ray *r, t_intersection *dst)
{
	dst->shape = sp;
	dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
	dst->x_img_comp = atan2f(dst->p.z - sp->o.z, dst->p.x - sp->o.x);
	if (dst->x_img_comp < 0.0f)
		dst->x_img_comp += 2.0f * PI;
	dst->x_img_comp /= (2 * PI);
	dst->y_img_comp = acosf(numerical_min((dst->p.y - sp->o.y)
				/ sp->r, sign(dst->p.y - sp->o.y))) / PI;
	dst->surf_n = sphere_surf_n(sp, dst);
	dst->color = point_color(sp->check, &sp->txt, sp->color, dst);
}

void	set_top_inter_vals(t_top *t, float h, t_ray *r, t_intersection *dst)
{
	t_vector	po;

	dst->shape = t->shape;
	dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
	po = vector_sub(dst->p, t->o);
	dst->x_img_comp = atan2f(vector_dot_prod(po, t->e_z),
			vector_dot_prod(po, t->e_y));
	if (dst->x_img_comp < 0.0f)
		dst->x_img_comp += 2.0f * PI;
	dst->x_img_comp /= 2 * PI;
	if (!h)
		dst->y_img_comp = vector_norm(po) / t->h_max;
	else
		dst->y_img_comp = (h + t->r - vector_norm(po)) / t->h_max;
	dst->surf_n = top_surf_n(t, dst);
	dst->color = point_color(t->check, t->txt, t->color, dst);
}

void	set_cylinder_inter_vals(t_cylinder *cy, t_ray *r, t_intersection *dst)
{
	t_vector	po;

	dst->shape = cy;
	dst->p = vector_add(r->o, vector_scale(r->n, dst->distance));
	po = vector_sub(dst->p, cy->o);
	dst->x_img_comp = atan2f(vector_dot_prod(po, cy->e_z),
			vector_dot_prod(po, cy->e_y));
	if (dst->x_img_comp < 0.0f)
		dst->x_img_comp += 2.0f * PI;
	dst->x_img_comp /= 2 * PI;
	dst->y_img_comp = (cy->h + vector_dot_prod(po, cy->n) + cy->r) / (2 * cy->r
			+ 2 * cy->h);
	dst->color = point_color(cy->check, &cy->txt, cy->color, dst);
	dst->surf_n = cylinder_surf_n(cy, dst);
}

void	set_cone_inter_vals(t_cone *co, t_ray *r, t_intersection *dst)
{
	t_vector	po;

	dst->shape = co;
	dst->p = point_on_ray(r, dst->distance);
	po = vector_sub(dst->p, co->o);
	dst->x_img_comp = atan2f(vector_dot_prod(po, co->e_z),
			vector_dot_prod(po, co->e_y));
	if (dst->x_img_comp < 0.0f)
		dst->x_img_comp += 2.0f * PI;
	dst->x_img_comp /= 2 * PI;
	dst->y_img_comp = (vector_dot_prod(po, co->n))
		/ (co->h * (1 + co->tan_a));
	dst->color = point_color(co->check, &co->txt, co->color, dst);
	dst->surf_n = cone_surf_n(co, dst);
}
