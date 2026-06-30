/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:43:36 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 10:33:10 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	parse_plane(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = PLANE;
	if (v_env->planes_count && !(v_env->planes_count % 8)
		&& extend_planes_len(p->env))
		return (true);
	if (go_to_next_field("origin", p)
		|| get_vector(&v_env->planes[v_env->planes_count].o,
			(float [2]){-1023.99996, 1023.99996}, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->planes[v_env->planes_count].n,
			(float [2]){-1.0, 1.0}, p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->planes[v_env->planes_count].color, p)
		|| check_end_of_obj(p))
		return (true);
	v_env->planes_count++;
	return (false);
}

bool	parse_sphere(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = SPHERE;
	if (v_env->spheres_count && !(v_env->spheres_count % 8)
		&& extend_spheres_len(p->env))
		return (true);
	if (go_to_next_field("origin", p)
		|| get_vector(&v_env->spheres[v_env->spheres_count].o,
			(float [2]){-1023.99996, 1023.99996}, p)
		|| go_to_next_field("diameter", p)
		|| get_float(&v_env->spheres[v_env->spheres_count].r,
			(float [2]){-1023.99996, 1023.99996}, false, p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->spheres[v_env->spheres_count].color, p)
		|| check_end_of_obj(p))
		return (true);
	v_env->spheres[v_env->spheres_count].r /= 2.0f;
	v_env->spheres_count++;
	return (false);
}

static bool	parse_cylinder_floats(t_parsing *p, t_visual_env *v_env)
{
	if (go_to_next_field("diameter", p)
		|| get_float(&v_env->cylinders[v_env->cylinders_count].r,
			(float [2]){-1023.99996, 1023.99996}, false, p)
		|| go_to_next_field("height", p)
		|| get_float(&v_env->cylinders[v_env->cylinders_count].h,
			(float [2]){-1023.99996, 1023.99996}, false, p))
		return (true);
	v_env->cylinders[v_env->cylinders_count].r /= 2.0f;
	v_env->cylinders[v_env->cylinders_count].h /= 2.0f;
	return (false);
}

bool	parse_cylinder(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = CYLINDER;
	if (v_env->cylinders_count && !(v_env->cylinders_count % 8)
		&& extend_cylinders_len(p->env))
		return (true);
	if (go_to_next_field("origin", p)
		|| get_vector(&v_env->cylinders[v_env->cylinders_count].o,
			(float [2]){-1023.99996, 1023.99996}, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->cylinders[v_env->cylinders_count].n,
			(float [2]){-1.0, 1.0}, p)
		|| parse_cylinder_floats(p, v_env)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->cylinders[v_env->cylinders_count].color, p)
		|| check_end_of_obj(p))
		return (true);
	v_env->cylinders_count++;
	return (false);
}
