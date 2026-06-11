/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:13:28 by almighty          #+#    #+#             */
/*   Updated: 2026/06/11 13:08:16 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../../includes/env.h"
#include "../../includes/parsing.h"

static bool	init_parsing(t_parsing *p, t_env *env)
{
	p->line = NULL;
	p->file.fd = open(env->file_name, O_RDONLY);
	if (p->file.fd == -1)
	{
		env->err = OPEN_ERR;
		return (true);
	}
	p->file.eof = false;
	p->file.buff_i = 0;
	p->file.read_len = 0;
	p->line_count = 0;
	p->parsing_id = 0;
	p->eop = false;
	p->comma_expected = false;
	p->curr_field_name = NULL;
	p->parsing_err = NO_PARSING_ERR;
	p->env = env;
	if (go_to_next_line(&p->file, p))
	{
		free(p->line);
		close(p->file.fd);
		return (true);
	}
	return (false);
}

static bool	parse_shape(t_parsing *p)
{
	if (p->line[p->line_i] == 'p' && p->line[p->line_i + 1] == 'l'
		&& (!p->line[p->line_i + 2] || p->line[p->line_i + 2] == ' '))
		return (parse_plane(p, &p->env->vis_env));
	if (p->line[p->line_i] == 's' && p->line[p->line_i + 1] == 'p'
		&& (!p->line[p->line_i + 2] || p->line[p->line_i + 2] == ' '))
		return (parse_sphere(p, &p->env->vis_env));
	else if (p->line[p->line_i] == 'c' && p->line[p->line_i + 1] == 'y'
		&& (!p->line[p->line_i + 2] || p->line[p->line_i + 2] == ' '))
		return (parse_cylinder(p, &p->env->vis_env));
	else
	{
		p->parsing_err = UNKNOWN_ELEMENT_ERR;
		return (true);
	}
	return (false);
}

static bool	parse_obj(t_parsing *p)
{
	if (!p->line[p->line_i])
		return (false);
	if (p->line[p->line_i] == 'A'
		&& (!p->line[p->line_i + 1] || p->line[p->line_i + 1] == ' '))
		return (parse_alight(p, &p->env->vis_env));
	else if (p->line[p->line_i] == 'C'
		&& (!p->line[p->line_i + 1] || p->line[p->line_i + 1] == ' '))
		return (parse_cam(p, &p->env->vis_env));
	else if (p->line[p->line_i] == 'L'
		&& (!p->line[p->line_i + 1] || p->line[p->line_i + 1] == ' '))
		return (parse_light(p, &p->env->vis_env));
	else
		return (parse_shape(p));
	return (false);
}

bool	parse_file(t_env *env)
{
	t_parsing	p;

	if (init_parsing(&p, env))
		return (true);
	while (!p.eop)
	{
		if (go_to_next_obj(&p)
			|| parse_obj(&p))
		{
			if (p.parsing_err)
				print_parsing_error(&p);
			free(p.line);
			return (true);
		}
	}
	free(p.line);
	return (false);
}
