/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:26:36 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:31:19 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env_bonus.h"
#include "../../includes/parsing_bonus.h"

bool	is_end_of_field(t_parsing *p)
{
	return (p->eop || p->line[p->line_i] == ' ' || !p->line[p->line_i]);
}

bool	go_to_next_obj(t_parsing *p)
{
	while (!p->eop && (!p->line[p->line_i] || p->line[p->line_i] == ' '))
	{
		if (!p->line[p->line_i])
		{
			if (go_to_next_line(&p->file, p))
				return (true);
			p->line_count++;
		}
		else
			p->line_i++;
	}
	p->curr_field_i = p->line_i;
	return (false);
}

bool	go_to_next_field(char *field_name, t_parsing *p)
{
	p->curr_field_name = field_name;
	while (p->line[p->line_i] && p->line[p->line_i] != ' ')
		p->line_i++;
	while (p->line[p->line_i] == ' ')
		p->line_i++;
	if (!p->line[p->line_i])
	{
		p->parsing_err = MISSING_FIELD_ERR;
		return (true);
	}
	p->curr_field_i = p->line_i;
	return (false);
}

bool	check_end_of_obj(t_parsing *p)
{
	while (p->line[p->line_i] == ' ')
		p->line_i++;
	if (p->line[p->line_i])
	{
		p->parsing_err = EXTRA_FIELD_ERR;
		return (true);
	}
	return (false);
}
