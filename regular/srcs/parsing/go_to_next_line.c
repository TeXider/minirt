/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:00:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/11 21:48:30 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	refresh_buffer(t_file *f, t_parsing *p)
{
	f->read_len = read(f->fd, f->buff, BUFF_SIZE);
	if (f->read_len == -1)
	{
		p->env->err = READ_ERR;
		return (true);
	}
	f->buff_i = 0;
	f->eof = (f->read_len == 0);
	return (false);
}

static bool	alloc_curr_line(size_t *len, t_file *f, t_parsing *p)
{
	size_t	i;
	char	*tmp;

	if (*len && f->read_len && f->read_len < BUFF_SIZE)
		return (false);
	if (!*len)
	{
		*len = BUFF_SIZE;
		if (challoc(&p->line, *len, p->env))
			return (true);
	}
	else
	{
		if (challoc(&tmp, *len + BUFF_SIZE, p->env))
			return (true);
		i = -1;
		while (++i < *len)
			tmp[i] = p->line[i];
		free(p->line);
		p->line = tmp;
		*len += BUFF_SIZE;
	}
	return (0);
}

static bool	end_next_line(t_file *f, t_parsing *p)
{
	p->line[p->line_i] = '\0';
	p->line_i = 0;
	f->buff_i++;
	return (f->buff_i == (size_t) f->read_len && refresh_buffer(f, p));
}

bool	go_to_next_line(t_file *f, t_parsing *p)
{
	size_t	line_len;

	if (f->eof)
	{
		p->eop = true;
		return (false);
	}
	safe_free((void **) &p->line);
	line_len = 0;
	if (alloc_curr_line(&line_len, f, p)
		|| (!f->read_len && refresh_buffer(f, p)))
		return (true);
	p->line_i = 0;
	while (!f->eof && f->buff[f->buff_i] && f->buff[f->buff_i] != '\n')
	{
		p->line[p->line_i] = f->buff[f->buff_i];
		p->line_i++;
		f->buff_i++;
		if (f->buff_i == (size_t) f->read_len
			&& (alloc_curr_line(&line_len, f, p)
				|| refresh_buffer(f, p)))
			return (true);
	}
	return (end_next_line(f, p));
}
