/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 01:39:41 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 01:54:53 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static bool	is_in_cone_shadow(t_ray *light_r, float dis_to_light, void *shape,
	t_visual_env *v_env)
{
	t_intersection	inter;
	size_t			i;

	i = -1;
	while (++i < v_env->cones_count)
		if (v_env->cones + i != shape
			&& get_cone_intersection(v_env->cones + i, light_r, &inter)
			&& inter.distance < dis_to_light)
			return (true);
	return (false);
}

bool	is_in_shadow(t_ray *light_r, float dis_to_light, void *shape,
	t_visual_env *v_env)
{
	t_intersection	inter;
	size_t			i;

	i = -1;
	while (++i < v_env->planes_count)
		if (v_env->planes + i != shape
			&& get_plane_intersection(v_env->planes + i, light_r, &inter)
			&& inter.distance < dis_to_light)
			return (true);
	i = -1;
	while (++i < v_env->spheres_count)
		if (v_env->spheres + i != shape
			&& get_sphere_intersection(v_env->spheres + i, light_r, &inter)
			&& inter.distance < dis_to_light)
			return (true);
	i = -1;
	while (++i < v_env->cylinders_count)
		if (v_env->cylinders + i != shape
			&& get_cylinder_intersection(v_env->cylinders + i, light_r, &inter)
			&& inter.distance < dis_to_light)
			return (true);
	return (is_in_cone_shadow(light_r, dis_to_light, shape, v_env));
}
