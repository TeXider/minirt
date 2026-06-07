/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_norm_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:28:23 by almighty          #+#    #+#             */
/*   Updated: 2026/06/04 22:06:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

t_vector	sphere_surface_norm_vector(t_sphere *sp, t_vector *p)
{
	t_vector	v;

	v = vector_sub(&sp->o, p);
	vector_normalize(&v);
	return (v);
}