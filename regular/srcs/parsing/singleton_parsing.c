/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:43:36 by almighty          #+#    #+#             */
/*   Updated: 2026/06/11 21:06:33 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	parse_alight(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = ALIGHT;
	if (v_env->has_alight)
	{
		p->parsing_err = MULTI_DEF_ERR;
		return (true);
	}
	if (go_to_next_field("intensity", p)
		|| get_float(&v_env->alight.intensity, (float[2]){0.0, 1.0}, false, p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->alight.color, p)
		|| check_end_of_obj(p))
	{
		p->parsing_err = INVALID_FIELD_ERR;
		return (true);
	}
	v_env->has_alight = true;
	return (false);
}

bool	parse_cam(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = CAM;
	if (v_env->has_cam)
	{
		p->parsing_err = MULTI_DEF_ERR;
		return (true);
	}
	if (go_to_next_field("position", p)
		|| get_vector(&v_env->cam.o, (float[2]){-1023.99996, 1023.99996}, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->cam.n, (float[2]){-1.0, 1.0}, p)
		|| go_to_next_field("horizontal_fov", p)
		|| get_int(&v_env->cam.h_fov, (int[2]){0, 180}, false, p)
		|| check_end_of_obj(p))
	{
		p->parsing_err = INVALID_FIELD_ERR;
		return (true);
	}
	v_env->has_cam = true;
	return (false);
}

bool	parse_light(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_id = CAM;
	if (v_env->has_cam)
	{
		p->parsing_err = MULTI_DEF_ERR;
		return (true);
	}
	if (go_to_next_field("position", p)
		|| get_vector(&v_env->light.o, (float[2]){-1023.99996, 1023.99996}, p)
		|| go_to_next_field("intensity", p)
		|| get_float(&v_env->light.intensity, (float[2]){0.0, 1.0}, false, p)
		|| check_end_of_obj(p))
	{
		p->parsing_err = INVALID_FIELD_ERR;
		return (true);
	}
	v_env->has_light = true;
	return (false);
}
