/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_surf_n2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:58:20 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:32:05 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_math_bonus.h"

static t_vector	init_cone_surf_n(t_intersection *dst, t_cone *co)
{
	t_vector	po;
	t_vector	h;

	po = vector_sub(dst->p, co->o);
	h = vector_scale(co->n, vector_dot_prod(po, co->n));
	return (vector_normalize(vector_sub(vector_sub(po, h),
				vector_scale(h, co->tan_a * co->tan_a))));
}

t_vector	cone_surf_n(t_cone *co, t_intersection *inter)
{
	t_vector	surf_n;
	t_vector	e_y;
	t_vector	e_z;
	float		bump_comp[2];

	surf_n = init_cone_surf_n(inter, co);
	if (!co->bump.img)
		return (surf_n);
	e_y = vector_normalize(vector_sub(inter->p, co->o));
	e_z = (t_vector){e_y.y * surf_n.z - e_y.z * surf_n.y, e_y.z * surf_n.x
		- e_y.x * surf_n.z, e_y.x * surf_n.y - e_y.y * surf_n.x};
	compute_bump_comp(bump_comp, &co->bump, inter);
	return (vector_normalize(vector_add(surf_n, vector_sub(vector_scale(e_z,
						bump_comp[0]), vector_scale(e_y, bump_comp[1])))));
}
