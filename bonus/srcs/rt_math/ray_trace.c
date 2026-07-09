/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:41:36 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/09 02:04:04 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

static t_color	compute_spec(t_ray *r, t_ray *l_r, t_light *l,
	t_intersection *i)
{
	float	reflection_amount;

	reflection_amount = fmaxf(0.0f, vector_dot_prod(r->n, vector_sub(l_r->n,
					vector_scale(i->surf_n,
						2.0f * vector_dot_prod(i->surf_n, l_r->n)))));
	return (scale_color(l->color,
			0.02f * l->intensity * l->intensity * reflection_amount
			/ (1.0f + 0.02f * l->intensity - reflection_amount)));
}

static t_intersection	find_cone_intersection(t_ray *r,
	t_intersection final_inter, t_visual_env *v_env)
{
	t_intersection	inter;
	size_t			i;

	i = -1;
	while (++i < v_env->cones_count)
		if (get_cone_intersection(v_env->cones + i, r, &inter)
			&& inter.distance < final_inter.distance)
			final_inter = inter;
	return (final_inter);
}

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
	final_inter = find_cone_intersection(r, final_inter, v_env);
	return (final_inter);
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
		return ((t_color){0, 0, 0});
	return (add_colors(compute_spec(r, &light_ray, light, inter),
			scale_color(light_color(inter->color, light->color),
				light->intensity * fabs(dot))));
}

// / (1.0f + vector_square(point_to_light) * 0.01f)

void	ray_trace(t_ray *r, t_color *dst_color, t_visual_env *v_env)
{
	t_intersection	inter;
	size_t			i;

	*dst_color = (t_color){0, 0, 0};
	inter = find_shape_intersection(r, v_env);
	if (inter.shape)
	{
		i = -1;
		while (++i < v_env->lights_count)
			*dst_color = add_colors(compute_lighting(&v_env->lights[i], r,
						&inter, v_env), *dst_color);
		*dst_color = add_colors(light_color(inter.color, v_env->alight.color),
				*dst_color);
	}
}
