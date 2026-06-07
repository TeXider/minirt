/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:13:28 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 18:14:48 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../includes/env.h"
#include "../includes/parsing.h"

static bool	init_parsing(t_parsing *p, t_env *env)
{
	p->fd = open(env->file_name, O_RDONLY);
	if (p->fd == -1)
	{
		env->err = OPEN_ERR;
		return (true);
	}
	p->line_count = 0;
	p->parsing_ctxt = 0;
	p->curr_field_name = NULL;
	p->curr_field_i = 0;
	p->parsing_err = NO_PARSING_ERR;
	p->env = env;
	return (actualize_buffer(p));
}

static bool	parse_shape(t_parsing *p, t_visual_env *v_env)
{
	if (p->buff[p->i] == 's' && p->i + 1 < p->read_len
		&& p->buff[p->i + 1] == 'p'
		&& (p->i + 2 == p->read_len || p->buff[p->i + 2] == ' '))
			return (parse_sphere(p, v_env));
	else if (p->buff[p->i] == 'p' && p->i + 1 < p->read_len
		&& p->buff[p->i + 1] == 'l'
		&& (p->i + 2 == p->read_len || p->buff[p->i + 2] == ' '))
		return (parse_plane(p, v_env));
	else if (p->buff[p->i] == 'c' && p->i + 1 < p->read_len
		&& p->buff[p->i + 1] == 'y'
		&& (p->i + 2 == p->read_len || p->buff[p->i + 2] == ' '))
		return (parse_cylinder(p, v_env));
	else if (p->buff[p->i])
	{
		print_parsing_error(UNKNOWN_ELEMENT_ERR, p);
		return (true);
	}
	return (false);
}

static bool	parse_obj(t_parsing *p, t_visual_env *v_env)
{
	if (p->buff[p->i] == 'A'
		&& (p->i + 1 == p->read_len || p->buff[p->i + 1] == ' '))
		return (parse_alight(p, v_env));
	else if (p->buff[p->i] == 'C'
		&& (p->i + 1 == p->read_len || p->buff[p->i + 1] == ' '))
		return (parse_camera(p, v_env));
	else if (p->buff[p->i] == 'L'
		&& (p->i + 1 == p->read_len || p->buff[p->i + 1] == ' '))
		return (parse_camera(p, v_env));
	else
		return (parse_shape(p, v_env));
	return (false);
}

bool	parse_file(t_env *env)
{
	t_parsing	p;

	if (init_parsing(&p, &env))
		return (true);
	while (!p.is_parsing_over)
	{
		if (go_to_next_obj(&p)
			|| (!p.is_parsing_over && parse_obj(&p, &env->vis_env)))
		{
			env->err += (p.parsing_err != NO_PARSING_ERR)
				* (p.parsing_err - env->err);
			return (true);
		}
	}
	return (false);
}
