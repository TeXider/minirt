/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/29 14:49:33 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/shapes.h"

bool	get_plane_intersection(t_plane *pl, t_ray *ray, t_vector *res)
{
	t_vector	tmp;
	float		t;

	if (!vector_dot_product(&ray->n, &pl->n))
		return (false);
	t = -vector_dot_product(&ray->o, &pl->n)
		/ vector_dot_product(&ray->n, &pl->n);
	*res = point_on_ray(ray, t);
	return (true);
}

bool	get_sphere_intersection(t_sphere *sp, t_ray *ray,
	t_vector *res)
{
	float	d;

	d = (-2 * a * b - 2 * c * d + e)
		* (-2 * a * b - 2 * c * d + e)
		- 4 * (a * a + c * c)
		* (b * b + d * d - f * f - g * g);
}
