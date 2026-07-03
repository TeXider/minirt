/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:41:36 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/03 18:01:47 by tpanou-d         ###   ########.fr       */
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

static t_color	compute_lighting(t_light *light, t_ray *r,
	t_intersection *inter, t_visual_env *v_env)
{
	t_ray		light_ray;
	t_vector	point_to_light;
	float		dot;

	light_ray.o = inter->p;
	point_to_light = vector_sub(light->o, light_ray.o);
	light_ray.n = vector_normalize(point_to_light);
	dot = vector_dot_prod(light_ray.n, inter->surf_n);
	if (sign(vector_dot_prod(r->n, inter->surf_n)) == sign(dot)
		|| is_in_shadow(&light_ray, vector_norm(point_to_light),
			inter->shape, v_env))
		return ((t_color){0,0,0});
	t_color c  = scale_color(light_color(inter->color, light->color), light->intensity * fabs(dot));
	float	bruh = fmaxf(0.0f, vector_dot_prod(vector_scale(r->n, -1), vector_add(vector_scale(inter->surf_n, 2.0f * vector_dot_prod(inter->surf_n, light_ray.n)), vector_scale(light_ray.n, -1))));
	float	spec_i = 0.02f * bruh / (1.0f + 0.02f - bruh);
	return (add_colors(scale_color((t_color){255,255,255}, spec_i * 0.5f), c));
}

// / (1.0f + vector_square(point_to_light) * 0.01f)

void	ray_trace(t_ray *r, t_color *dst_color, t_visual_env *v_env)
{
	t_intersection	inter;
	t_color			lighting_color;
	size_t			i;

	inter = find_shape_intersection(r, v_env);
	if (!inter.shape)
		*dst_color = (t_color){0, 0, 0};
	else
	{
		lighting_color = (t_color){0, 0, 0};
		i = -1;
		while (++i < v_env->lights_count)
			lighting_color = add_colors(lighting_color,
					compute_lighting(&v_env->lights[i],
						r, &inter, v_env));
		*dst_color = add_colors(light_color(inter.color, v_env->alight.color),
				lighting_color);
	}
}
