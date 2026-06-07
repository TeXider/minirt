/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:26:36 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 17:46:11 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"
#include "../includes/parsing.h"

bool	actualize_buffer(t_parsing *p)
{
	p->read_len = read(p->fd, p->buff, 1028);
	if (p->read_len == -1)
	{
		p->env->err = READ_ERR;
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
		p->line_count += (p->buff[p->i] == '\n');
		p->i++;
		if (p->i == p->read_len)
		{
			if (actualize_buffer(p))
				return (true);
			p->i = 0;
		}
	}
	return (false);
}

bool	go_to_next_field(char *field_name, t_parsing *p)
{
	p->curr_field_name = field_name;
	while (!p->is_parsing_over && p->buff[p->i] == ' ')
	{
		p->i++;
		if (p->i == p->read_len)
		{
			if (actualize_buffer(p))
				return (true);
			p->i = 0;
		}
	}
	if (p->is_parsing_over || p->buff[p->i] == '\n')
	{
		p->parsing_err = MISSING_FIELD_ERR;
		return (true);
	}
	return (false);
}

bool	check_fields_over(t_parsing *p)
{
	while (!p->is_parsing_over && p->buff[p->i] == ' ')
	{
		p->i++;
		if (p->i == p->read_len)
		{
			if (actualize_buffer(p))
				return (true);
			p->i = 0;
		}
	}
	if (!p->is_parsing_over && p->buff[p->i] != '\n')
	{
		p->parsing_err = EXTRA_FIELD_ERR;
		return (true);
	}
	return (false);
}
