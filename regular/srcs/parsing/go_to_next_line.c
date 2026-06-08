/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:00:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/08 18:52:39 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	refresh_buffer(t_parsing *p)
{
	if (p->eof)
		return (false);
	p->read_len = read(p->fd, p->buff, 1024);
	if (p->read_len == -1)
	{
		p->env->err = READ_ERR;
		return (true);
	}
	p->buff_i = 0;
	p->eof = (p->read_len == 0);
	return (false);
}

static bool	alloc_curr_line(size_t *len, t_parsing *p)
{
	ssize_t	i;
	char	*tmp;

	if (!*len)
	{
		*len = 1024;
		if (challoc(&p->line, *len, p->env))
			return (true);
	}
	else
	{
		*len += 1024;
		if (challoc(&tmp, *len, p->env))
			return (true);
		i = -1;
		while (++i < *len)
			tmp[i] = p->line[i];
		free(p->line);
		p->line = tmp;
	}
	return (0);
}

bool	*go_to_next_line(t_parsing *p)
{
	size_t	line_len;

	safe_free(&p->line);
	line_len = 0;
	if (alloc_curr_line(&line_len, p)
		|| refresh_buffer(p))
		return (true);
	p->line_i = 0;
	while (!p->eof && p->buff[p->buff_i] && p->buff[p->buff_i] != '\n')
	{
		p->line[p->line_i] = p->buff[p->buff_i];
		p->line_i++;
		p->buff_i++;
		if (p->buff_i == p->read_len
			&& (alloc_curr_line(&line_len, p)
				|| refresh_buffer(p)))
			return (true);
	}
	p->line[p->line_i] = '\0';
	p->line_i = 0;
	p->buff_i++;
	return (p->buff_i == p->read_len && refresh_buffer(p));
}
