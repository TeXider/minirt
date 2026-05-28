/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:41:36 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/27 17:47:46 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray.h"

t_vector	point_on_ray(t_ray *ray, float t)
{
	t_vector	tmp;

	tmp = vector_scale(&ray->n, t);
	return (vector_add(&ray->o, &tmp));
}
