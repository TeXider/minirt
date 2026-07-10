/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape_vals_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 10:50:50 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:31:07 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/parsing_bonus.h"

void	init_plane_vals(t_plane *pl)
{
	pl->n = vector_normalize(pl->n);
	compute_basis(pl->n, &pl->e_y, &pl->e_z);
	pl->check = 0;
	pl->txt.img = NULL;
	pl->bump.img = NULL;
}

void	init_sphere_vals(t_sphere *sp)
{
	sp->r /= 2.0f;
	sp->check = 0;
	sp->bump.img = NULL;
	sp->txt.img = NULL;
}

void	init_cylinder_vals(t_cylinder *cy)
{
	cy->r /= 2.0f;
	cy->h /= 2.0f;
	cy->n = vector_normalize(cy->n);
	compute_basis(cy->n, &cy->e_y, &cy->e_z);
	cy->check = 0;
	cy->txt.img = NULL;
	cy->bump.img = NULL;
}

void	init_cone_vals(t_cone *co)
{
	co->a *= PI / 180.0f - 0.001f * (co->a == 180);
	co->tan_a = tanf(co->a);
	co->inter_k = 1 + co->tan_a * co->tan_a;
	co->n = vector_normalize(co->n);
	compute_basis(co->n, &co->e_y, &co->e_z);
	co->check = 0;
	co->txt.img = NULL;
	co->bump.img = NULL;
}
