/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_err2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:58:31 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/09 14:06:54 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	field_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

void	print_extra_field_error(t_parsing *p)
{
	printf("\e[1m↳ Extra field '\e[0m%.*s\e[1m' for \e[3m%s\e[23m"
		" on line %zu\e[0m\n\n",
		field_len(p->line + p->line_i), p->line + p->line_i,
		p->parsing_id, p->line_count + 1);
	print_declaration_hint(p->parsing_id);
}

void	print_out_of_range_error(t_parsing *p)
{
	printf("\e[1m↳ Field \e[3m<%s>\e[23m (\e[0m%.*s\e[1m) is out-of-range"
		" for \e[3m%s\e[23m on line %zu\e[0m\n\n", p->curr_field_name,
		field_len(p->line + p->curr_field_i),
		p->line + p->curr_field_i, p->parsing_id,
		p->line_count + 1);
	print_declaration_hint(p->parsing_id);
}

void	print_invalid_field_error(t_parsing *p)
{
	printf("\e[1m↳ Invalid field \e[3m<%s>\e[23m (\e[0m%.*s\e[1m)"
		" for \e[3m%s\e[23m on line %zu\n\n\e[0m",
		p->curr_field_name, field_len(p->line + p->curr_field_i),
		p->line + p->curr_field_i, p->parsing_id,
		p->line_count + 1);
	print_declaration_hint(p->parsing_id);
}

void	print_unknown_element_error(t_parsing *p)
{
	printf("\e[1m↳ Unknown element '\e[0m%.*s\e[1m' on line %zu\n\n",
		field_len(p->line + p->curr_field_i), p->line + p->curr_field_i,
		p->line_count + 1);
	printf("\e[1mⓘ\e[0m   Possible identifiers are \e[3mA\e[0m (alight),"
		"\e[3m C (camera)\e[0m, \e[3mL\e[0m (light), \e[3mpl\e[0m (plane)"
		", \e[3msp\e[0m (sphere) and \e[3mcy\e[0m (cylinder)\e[0m\n\n");
}
