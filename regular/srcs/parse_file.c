/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:13:28 by almighty          #+#    #+#             */
/*   Updated: 2026/06/03 11:00:25 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../includes/env.h"

static bool	actualize_buffer(t_parsing *p)
{
	p->read_len = read(p->fd, p->buff, 1028);
	if (read == -1)
	{
		print_error(READ_ERR, READ_ERR_HINT, NULL);
		return (true);
	}
	p->i = 0;
	p->is_parsing_over = (p->read_len == 0);
	return (false);
}

static bool	init_parsing(char *filename, t_parsing *p)
{
	p->fd = open(filename, O_RDONLY);
	if (p->fd == -1)
	{
		print_error(FILE_ERR, filename, NULL);
		return (true);
	}
	return (actualize_buffer(p));
}

static bool	go_to_next_obj(t_parsing *p)
{
	while (!p->is_parsing_over && p->buff[p->i] == ' ' && p->buff[p->i] == '\n')
	{
		p->i++;
		if (p->i == p->read_len && actualize_buffer(p))
			return (true);
	}
	return (false);
}

static bool	final_check(t_parsing *p)
{
	if (p->buff[p->i])
	{
		print_parsing_error();
	}
}

static bool	parse_shape(t_parsing *p, t_env *env)
{
	if (p->buff[p->i] == 's' && p->i + 1 < p->read_len
		&& p->buff[p->i + 1] == 's')
	{
		if (parse_sphere(p, env))
			return (true);
	}
	else if (p->buff[p->i] == 'p' && p->i + 1 < p->read_len
		&& p->buff[p->i + 1] == 'l')
	{
		if (parse_sphere(p, env))
			return (true);
	}
	else if (p->buff[p->i] == 'c' && p->i + 1 < p->read_len
		&& p->buff[p->i + 1] == 'y')
	{
		if (parse_sphere(p, env))
			return (true);
	}
	else
		return (final_check(p));
	return (false);
}

static bool	parse_obj(t_parsing *p, t_env *env)
{
	if (p->buff[p->i] == 'A')
	{
		if (parse_alighting(p, env))
			return (true);
	}
	else if (p->buff[p->i] == 'C')
	{
		if (parse_camera(p, env))
			return (true);
	}
	else if (p->buff[p->i] == 'L')
	{
		if (parse_light(p, env))
			return (true);
	}
	else
		return (parse_shape(p, env));
	return (false);
}

bool	parse_file(char *filename, t_env *env)
{
	t_parsing	p;

	if (init_parsing(filename, &p))
		return (true);
	while (!p.is_parsing_over)
		if (go_to_next_obj(&p)
			|| parse_obj(&p, env))
			return (true);
	return (false);
}
