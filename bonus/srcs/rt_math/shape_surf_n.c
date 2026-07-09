/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_surf_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:17:01 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 12:58:20 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/rt_math.h"

void	compute_bump_comp(float bc[2], t_img *bump, t_intersection *inter)
{
	float	dx;
	float	dy;
	float	p_min;
	float	p_plus;

	dx = 1.0f / bump->width;
	p_plus = inter->x_img_comp + dx;
	p_plus -= (p_plus > 1);
	p_min = inter->x_img_comp - dx;
	p_min += (p_min < 0);
	bc[0] = txt_intensity(p_plus, inter->y_img_comp, bump)
		- txt_intensity(p_min, inter->y_img_comp, bump);
	dy = 1.0f / bump->height;
	p_plus = inter->y_img_comp + dy;
	p_plus -= (p_plus > 1);
	p_min = inter->y_img_comp - dy;
	p_min += (p_min < 0);
	bc[1] = txt_intensity(inter->x_img_comp, p_plus, bump)
		- txt_intensity(inter->x_img_comp, p_min, bump);
	bc[0] *= 5;
	bc[1] *= 5;
}

t_vector	plane_surf_n(t_plane *pl, t_intersection *inter)
{
	float	bump_comp[2];

	if (!pl->bump.img)
		return (pl->n);
	compute_bump_comp(bump_comp, &pl->bump, inter);
	return (vector_normalize(vector_add(pl->n, vector_sub(vector_scale(pl->e_z,
						bump_comp[0]), vector_scale(pl->e_y, bump_comp[1])))));
}

t_vector	sphere_surf_n(t_sphere *sp, t_intersection *inter)
{
	t_vector	surf_n;
	t_vector	e_y;
	t_vector	e_z;
	float		bump_comp[2];

	surf_n = vector_scale(vector_sub(inter->p, sp->o), 1.0f / sp->r);
	if (!sp->bump.img)
		return (surf_n);
	compute_basis(surf_n, &e_y, &e_z);
	compute_bump_comp(bump_comp, &sp->bump, inter);
	return (vector_normalize(vector_add(surf_n, vector_sub(vector_scale(e_z,
						bump_comp[0]), vector_scale(e_y, bump_comp[1])))));
}

t_vector	cylinder_surf_n(t_cylinder *cy, t_intersection *inter)
{
	t_vector	surf_n;
	t_vector	e_y;
	t_vector	e_z;
	float		bump_comp[2];

	surf_n = vector_normalize(vector_sub(vector_sub(inter->p, cy->o),
				vector_scale(cy->n, vector_dot_prod(cy->n,
						vector_sub(inter->p, cy->o)))));
	if (!cy->bump.img)
		return (surf_n);
	e_y = cy->n;
	e_z = vector_add(vector_scale(cy->e_y, vector_dot_prod(cy->e_y, surf_n)),
			vector_scale(cy->e_z, vector_dot_prod(cy->e_z, surf_n)));
	compute_bump_comp(bump_comp, &cy->bump, inter);
	return (vector_normalize(vector_add(surf_n, vector_sub(vector_scale(e_z,
						bump_comp[0]), vector_scale(e_y, bump_comp[1])))));
}

t_vector	top_surf_n(t_top *t, t_intersection *inter)
{
	float	bump_comp[2];

	if (!t->bump->img)
		return (t->n);
	compute_bump_comp(bump_comp, t->bump, inter);
	return (vector_normalize(vector_add(t->n, vector_sub(vector_scale(t->e_z,
						bump_comp[0]), vector_scale(t->e_y, bump_comp[1])))));
}
