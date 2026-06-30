/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:41:36 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/30 11:22:09 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

static t_intersection	find_shape_intersection(t_ray *r, t_visual_env *v_env)
{
	t_intersection	final_inter;
	t_intersection	inter;
	size_t			i;

	final_inter.distance = INFINITY;
	final_inter.shape = NULL;
	i = -1;
	while (++i < v_env->planes_count)
		if (get_plane_intersection(v_env->planes + i, r, &inter)
			&& inter.distance < final_inter.distance)
			final_inter = inter;
	i = -1;
	while (++i < v_env->spheres_count)
		if (get_sphere_intersection(v_env->spheres + i, r, &inter)
			&& inter.distance < final_inter.distance)
			final_inter = inter;
	i = -1;
	while (++i < v_env->cylinders_count)
		if (get_cylinder_intersection(v_env->cylinders + i, r, &inter)
			&& inter.distance < final_inter.distance)
			final_inter = inter;
	return (final_inter);
}

static bool	is_in_shadow(t_ray *light_r, float dis_to_light, void *shape,
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
	return (false);
}

static t_color	compute_lighting(t_intersection *inter, t_ray *r,
	t_visual_env *v_env)
{
	t_ray		light_ray;
	t_vector	point_to_light;
	t_color		alight;
	t_color		light;

	alight = (t_color){0, 0, 0};
	light = (t_color){0, 0, 0};
	if (v_env->has_alight)
		alight = light_color(inter->color, v_env->alight.color);
	if (v_env->has_light)
	{
		light_ray.o = inter->p;
		point_to_light = vector_sub(v_env->light.o, light_ray.o);
		light_ray.n = vector_normalize(point_to_light);
		if (sign(vector_dot_prod(r->n, inter->surf_n))
			== sign(vector_dot_prod(light_ray.n, inter->surf_n))
			|| is_in_shadow(&light_ray, vector_norm(point_to_light),
				inter->shape, v_env))
			return (alight);
		light = scale_color(inter->color, v_env->light.intensity
				* fabs(vector_dot_prod(light_ray.n, inter->surf_n)));
	}
	return (add_colors(alight, light));
}

// / (1.0f + vector_square(point_to_light) * 0.01f)

void	ray_trace(t_ray *r, t_color *dst_color, t_visual_env *v_env)
{
	t_intersection	inter;

	inter = find_shape_intersection(r, v_env);
	if (!inter.shape)
		*dst_color = (t_color){0, 0, 0};
	else
		*dst_color = compute_lighting(&inter, r, v_env);
}
