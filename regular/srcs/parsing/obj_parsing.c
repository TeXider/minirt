/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:43:36 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 21:16:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	parse_alight(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_ctxt = ALIGHT;
	if (v_env->has_alight)
	{
		p->parsing_err = MULTI_DEF_ERR;
		return (true);
	}
	p->i++;
	if (go_to_next_field("intensity", p)
		|| get_float(&v_env->alight.intensity, 0.0, 1.0, p)
		|| go_to_next_field("color", p)
		|| get_color(&v_env->alight.color, p)
		|| check_fields_over(p))
		return (true);
	{
		p->parsing_err = EXTRA_FIELD_ERR;
		return (true);
	}
	v_env->has_alight = true;
	return (false);
}

bool	parse_cam(t_parsing *p, t_visual_env *v_env)
{
	p->parsing_ctxt = CAM;
	if (v_env->has_cam)
	{
		p->parsing_err = MULTI_DEF_ERR;
		return (true);
	}
	p->i++;
	if (go_to_next_field("position", p)
		|| get_vector(&v_env->cam.o, -999.0, 999.0, p)
		|| go_to_next_field("normal_vector", p)
		|| get_vector(&v_env->cam.n, -1.0, 1.0, p)
		|| go_to_next_field("horizontal_fov", p)
		|| get_int(&v_env->cam.h_fov, 0, 180, p)
		|| check_fields_over(p))
		return (true);
	{
		p->parsing_err = EXTRA_FIELD_ERR;
		return (true);
	}
	v_env->has_alight = true;
	return (false);
}
