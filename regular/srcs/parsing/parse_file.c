/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:13:28 by almighty          #+#    #+#             */
/*   Updated: 2026/06/08 19:27:26 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../includes/env.h"
#include "../includes/parsing.h"

static bool	init_parsing(t_parsing *p, t_env *env)
{
	p->line = NULL;
	p->fd = open(env->file_name, O_RDONLY);
	if (p->fd == -1)
	{
		env->err = OPEN_ERR;
		return (true);
	}
	p->eof = false;
	p->line_count = 0;
	p->parsing_id = 0;
	p->comma_expected = false;
	p->curr_field_name = NULL;
	p->parsing_err = NO_PARSING_ERR;
	p->env = env;
	if (go_to_next_line(p))
	{
		close(p->fd);
		return (true);
	}
	return (false);
}

static bool	parse_shape(t_parsing *p)
{
	if (p->line[p->line_i] == 'p' && p->line[p->line_i + 1] == 'l'
		&& !(p->line[p->line_i + 2] || p->line[p->line_i + 2] == ' '))
		return (parse_plane(p, p->env->vis_env));
	if (p->line[p->line_i] == 's' && p->line[p->line_i + 1] == 'p'
		&& !(p->line[p->line_i + 2] || p->line[p->line_i + 2] == ' '))
		return (parse_sphere(p, p->env->vis_env));
	else if (p->line[p->line_i] == 'c' && p->line[p->line_i + 1] == 'y'
		&& !(p->line[p->line_i + 2] || p->line[p->line_i + 2] == ' '))
		return (parse_cylinder(p, p->env->vis_env));
	else
	{
		p->parsing_err = UNKNOWN_ELEMENT_ERR;
		return (true);
	}
	return (false);
}

static bool	parse_obj(t_parsing *p)
{
	if (p->eof)
		return (false);
	if (p->line[p->line_i] == 'A'
		&& !(p->line[p->line_i + 1] || p->line[p->line_i + 1] == ' '))
		return (parse_alight(p, p->env->vis_env));
	else if (p->line[p->line_i] == 'C'
		&& !(p->line[p->line_i + 1] || p->line[p->line_i + 1] == ' '))
		return (parse_camera(p, p->env->vis_env));
	else if (p->line[p->line_i] == 'L'
		&& !(p->line[p->line_i + 1] || p->line[p->line_i + 1] == ' '))
		return (parse_light(p, p->env->vis_env));
	else
		return (parse_shape(p));
	return (false);
}

bool	parse_file(t_env *env)
{
	t_parsing	p;

	if (init_parsing(&p, &env))
		return (true);
	while (!p.eof)
	{
		if (go_to_next_obj(&p)
			|| parse_obj(&p))
		{
			env->err += !env->err * p.parsing_err;
			return (true);
		}
	}
	return (false);
}
