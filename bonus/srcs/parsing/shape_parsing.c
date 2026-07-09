/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:43:36 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 17:47:41 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/parsing.h"

bool	parse_plane(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = PLANE;
	if (v_env->planes_count && !(v_env->planes_count % 8)
		&& extend_planes_len(p->env))
		return (true);
	if (go_to_next_field("origin", p)
		|| get_vector(&v_env->planes[v_env->planes_count].o,
			(float [2]){-INFINITY, INFINITY}, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->planes[v_env->planes_count].n,
			(float [2]){-1.0, 1.0}, p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->planes[v_env->planes_count].color, p))
		return (true);
	init_plane_vals(&v_env->planes[v_env->planes_count]);
	v_env->planes_count++;
	return (check_pl_options(&v_env->planes[v_env->planes_count - 1], p)
		|| check_end_of_obj(p));
}

bool	parse_sphere(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = SPHERE;
	if (v_env->spheres_count && !(v_env->spheres_count % 8)
		&& extend_spheres_len(p->env))
		return (true);
	if (go_to_next_field("origin", p)
		|| get_vector(&v_env->spheres[v_env->spheres_count].o,
			(float [2]){-INFINITY, INFINITY}, p)
		|| go_to_next_field("diameter", p)
		|| get_float(&v_env->spheres[v_env->spheres_count].r,
			(float [2]){0, INFINITY}, '\0', p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->spheres[v_env->spheres_count].color, p))
		return (true);
	init_sphere_vals(&v_env->spheres[v_env->spheres_count]);
	v_env->spheres_count++;
	return (check_sp_options(&v_env->spheres[v_env->spheres_count - 1], p)
		|| check_end_of_obj(p));
}

bool	parse_cylinder(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = CYLINDER;
	if (v_env->cylinders_count && !(v_env->cylinders_count % 8)
		&& extend_cylinders_len(p->env))
		return (true);
	if (go_to_next_field("origin", p)
		|| get_vector(&v_env->cylinders[v_env->cylinders_count].o,
			(float [2]){-INFINITY, INFINITY}, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->cylinders[v_env->cylinders_count].n,
			(float [2]){-1.0, 1.0}, p)
		|| go_to_next_field("diameter", p)
		|| get_float(&v_env->cylinders[v_env->cylinders_count].r,
			(float [2]){0, INFINITY}, '\0', p)
		|| go_to_next_field("height", p)
		|| get_float(&v_env->cylinders[v_env->cylinders_count].h,
			(float [2]){0, INFINITY}, '\0', p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->cylinders[v_env->cylinders_count].color, p))
		return (true);
	init_cylinder_vals(&v_env->cylinders[v_env->cylinders_count]);
	v_env->cylinders_count++;
	return (check_cy_options(&v_env->cylinders[v_env->cylinders_count - 1], p)
		|| check_end_of_obj(p));
}

bool	parse_cone(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = CONE;
	if (v_env->cones_count && !(v_env->cones_count % 8)
		&& extend_cones_len(p->env))
		return (true);
	if (go_to_next_field("origin", p)
		|| get_vector(&v_env->cones[v_env->cones_count].o,
			(float [2]){-INFINITY, INFINITY}, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->cones[v_env->cones_count].n,
			(float [2]){-1.0, 1.0}, p)
		|| go_to_next_field("angle", p)
		|| get_float(&v_env->cones[v_env->cones_count].a,
			(float [2]){0, 180}, '\0', p)
		|| go_to_next_field("height", p)
		|| get_float(&v_env->cones[v_env->cones_count].h,
			(float [2]){0, INFINITY}, '\0', p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->cones[v_env->cones_count].color, p))
		return (true);
	init_cone_vals(&v_env->cones[v_env->cones_count]);
	v_env->cones_count++;
	return (check_co_options(&v_env->cones[v_env->cones_count - 1], p)
		|| check_end_of_obj(p));
}
