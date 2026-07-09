/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape_vals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 10:50:50 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 01:22:53 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/parsing.h"

void	init_plane_vals(t_plane *pl, void *mlx_ptr)
{
	pl->n = vector_normalize(pl->n);
	compute_basis(pl->n, &pl->e_y, &pl->e_z);
	pl->txt.img = NULL;
	pl->bump.img = NULL;
}

void	init_sphere_vals(t_sphere *sp, void *mlx_ptr)
{
	sp->r /= 2.0f;
	sp->txt.img = NULL;
	sp->bump.img = NULL;
}

void	init_cylinder_vals(t_cylinder *cy)
{
	cy->r /= 2.0f;
	cy->h /= 2.0f;
	cy->n = vector_normalize(cy->n);
	cy->check = 10;
	cy->txt.img = NULL;
	cy->bump.img = NULL;
	compute_basis(cy->n, &cy->e_y, &cy->e_z);
}

void	init_cone_vals(t_cone *co)
{
	co->a *= PI / 180.0f;
	co->tan_a = tanf(co->a);
	co->inter_k = 1 + co->tan_a * co->tan_a;
	co->n = vector_normalize(co->n);
	co->check = 16;
	co->txt.img = NULL;
	co->bump.img = NULL;
	compute_basis(co->n, &co->e_y, &co->e_z);
}
