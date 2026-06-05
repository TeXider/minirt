/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:26:36 by almighty          #+#    #+#             */
/*   Updated: 2026/06/04 22:11:10 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"
#include "../includes/parsing.h"

bool	actualize_buffer(t_parsing *p)
{
	p->read_len = read(p->fd, p->buff, 1028);
	if (p->read_len == -1)
	{
		print_error(READ_ERR, NULL);
		return (true);
	}
	p->i = 0;
	p->is_parsing_over = (p->read_len == 0);
	return (false);
}

bool	go_to_next_obj(t_parsing *p)
{
	while (!p->is_parsing_over
		&& (p->buff[p->i] == ' ' || p->buff[p->i] == '\n'))
	{
		p->i++;
		if (p->i == p->read_len && actualize_buffer(p))
			return (true);
	}
	return (false);
}

bool	go_to_next_field(t_parsing *p)
{
	while (!p->is_parsing_over && p->buff[p->i] == ' ')
	{
		p->i++;
		if (p->i == p->read_len && actualize_buffer(p))
			return (true);
	}
	return (false);
}
