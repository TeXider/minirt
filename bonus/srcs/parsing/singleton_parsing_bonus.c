/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_parsing_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:43:36 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:31:34 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/parsing_bonus.h"

bool	parse_alight(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = ALIGHT;
	if (v_env->has_alight)
	{
		p->parsing_err = MULTI_DEF_ERR;
		return (true);
	}
	if (go_to_next_field("intensity", p)
		|| get_float(&v_env->alight.intensity, (float [2]){0.0, 1.0}, '\0', p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->alight.color, p)
		|| check_end_of_obj(p))
		return (true);
	v_env->has_alight = true;
	v_env->alight.color = scale_color(v_env->alight.color,
			v_env->alight.intensity);
	return (false);
}

bool	parse_cam(t_parsing *p, t_visual_env *v_env)
{
	int	h_fov_int;

	p->parsing_id = CAM;
	if (v_env->has_cam)
	{
		p->parsing_err = MULTI_DEF_ERR;
		return (true);
	}
	if (go_to_next_field("position", p)
		|| get_vector(&v_env->cam.o, (float [2]){-INFINITY, INFINITY}, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->cam.n, (float [2]){-1.0, 1.0}, p)
		|| go_to_next_field("horizontal_fov", p)
		|| get_int(&h_fov_int, (int [2]){0, 180}, '\0', p))
		return (true);
	v_env->has_cam = true;
	v_env->cam.h_fov = ((float) h_fov_int - 0.001f * (h_fov_int == 180))
		* 3.1415926f / 180.0f;
	v_env->cam.n = vector_normalize(v_env->cam.n);
	compute_basis(v_env->cam.n, &v_env->cam.e_y, &v_env->cam.e_z);
	v_env->cam.r_x = 1280;
	v_env->cam.r_y = 720;
	return (check_cam_options(&v_env->cam, v_env, p)
		|| check_end_of_obj(p));
}

bool	parse_light(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = LIGHT;
	if (v_env->lights_count && !(v_env->lights_count % 8)
		&& extend_lights_len(p->env))
		return (true);
	if (go_to_next_field("position", p)
		|| get_vector(&v_env->lights[v_env->lights_count].o,
			(float [2]){-INFINITY, INFINITY}, p)
		|| go_to_next_field("intensity", p)
		|| get_float(&v_env->lights[v_env->lights_count].intensity,
			(float [2]){0.0, 1.0}, '\0', p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->lights[v_env->lights_count].color, p)
		|| check_end_of_obj(p))
		return (true);
	v_env->lights_count++;
	return (false);
}
