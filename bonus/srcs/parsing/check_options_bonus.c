/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 09:03:29 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:30:53 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/parsing_bonus.h"

bool	check_cam_options(t_camera *cam, t_visual_env *v_env, t_parsing *p)
{
	if (go_to_next_field("options", p))
	{
		p->parsing_err = NO_ERR;
		return (false);
	}
	while (p->line[p->line_i] && p->line[p->line_i] != ' '
		&&!p->env->err && !p->parsing_err)
	{
		if (check_option("res", p) && !(cam->r_x == 1280 && cam->r_y == 720))
			parse_cam_res(cam, p);
		else if (check_option("aa", p) && !v_env->aa)
			get_int(&v_env->aa, (int [2]){0, 5}, ';', p);
		else if (check_option("sky", p) && !v_env->sky_box.img)
			parse_txt(&v_env->sky_box, p);
		else
			p->parsing_err = INVALID_OPT_ERR;
	}
	if (p->parsing_err)
		p->parsing_err = INVALID_OPT_ERR;
	return (p->parsing_err || p->env->err);
}

bool	check_pl_options(t_plane *pl, t_parsing *p)
{
	if (go_to_next_field("options", p))
	{
		p->parsing_err = NO_ERR;
		return (false);
	}
	while (p->line[p->line_i] && p->line[p->line_i] != ' '
		&&!p->env->err && !p->parsing_err)
	{
		if (check_option("txt", p) && !pl->txt.img)
			parse_txt(&pl->txt, p);
		else if (check_option("bump", p) && !pl->bump.img)
			parse_txt(&pl->bump, p);
		else if (check_option("check", p) && !pl->check)
			get_float(&pl->check, (float [2]){0.0, INFINITY}, ';', p);
		else
			p->parsing_err = INVALID_OPT_ERR;
	}
	if (p->parsing_err)
		p->parsing_err = INVALID_OPT_ERR;
	pl->check += (!pl->check && (pl->txt.img || pl->bump.img));
	return (p->parsing_err || p->env->err);
}

bool	check_sp_options(t_sphere *sp, t_parsing *p)
{
	if (go_to_next_field("options", p))
	{
		p->parsing_err = NO_ERR;
		return (false);
	}
	while (p->line[p->line_i] && p->line[p->line_i] != ' '
		&&!p->env->err && !p->parsing_err)
	{
		if (check_option("txt", p) && !sp->txt.img)
			parse_txt(&sp->txt, p);
		else if (check_option("bump", p) && !sp->bump.img)
			parse_txt(&sp->bump, p);
		else if (check_option("check", p) && !sp->check)
			get_int(&sp->check, (int [2]){0, 100}, ';', p);
		else
			p->parsing_err = INVALID_OPT_ERR;
	}
	if (p->parsing_err)
		p->parsing_err = INVALID_OPT_ERR;
	return (p->parsing_err || p->env->err);
}

bool	check_cy_options(t_cylinder *cy, t_parsing *p)
{
	if (go_to_next_field("options", p))
	{
		p->parsing_err = NO_ERR;
		return (false);
	}
	while (p->line[p->line_i] && p->line[p->line_i] != ' '
		&&!p->env->err && !p->parsing_err)
	{
		if (check_option("txt", p) && !cy->txt.img)
			parse_txt(&cy->txt, p);
		else if (check_option("bump", p) && !cy->bump.img)
			parse_txt(&cy->bump, p);
		else if (check_option("check", p) && !cy->check)
			get_int(&cy->check, (int [2]){0, 100}, ';', p);
		else
			p->parsing_err = INVALID_OPT_ERR;
	}
	if (p->parsing_err)
		p->parsing_err = INVALID_OPT_ERR;
	return (p->parsing_err || p->env->err);
}

bool	check_co_options(t_cone *co, t_parsing *p)
{
	if (go_to_next_field("options", p))
	{
		p->parsing_err = NO_ERR;
		return (false);
	}
	while (p->line[p->line_i] && p->line[p->line_i] != ' '
		&&!p->env->err && !p->parsing_err)
	{
		if (check_option("txt", p) && !co->txt.img)
			parse_txt(&co->txt, p);
		else if (check_option("bump", p) && !co->bump.img)
			parse_txt(&co->bump, p);
		else if (check_option("check", p) && !co->check)
			get_int(&co->check, (int [2]){0, 100}, ';', p);
		else
			p->parsing_err = INVALID_OPT_ERR;
	}
	if (p->parsing_err)
		p->parsing_err = INVALID_OPT_ERR;
	return (p->parsing_err || p->env->err);
}
