/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:55:58 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/08 11:36:06 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	print_multi_def_error(t_parsing *p)
{
	printf("\e[1m↳ Extraneous \e[3m%s\e[23m definition on line %zu\e[0m\n\n",
		p->parsing_id, p->line_count + 1);
	printf("\e[1mⓘ\e[0m   There can only be one definition for \e[3m%s\e[0m "
		"(%c) in a .rt scene\e[0m\n\n", p->parsing_id, p->parsing_id[0]);
	print_declaration_hint(p->parsing_id[0]);
}

static void	print_missing_field_error(t_parsing *p)
{
	printf("\e[1m↳ Missing field \e[3m<%s>\e[23m for \e[3m%s\e[23m"
		" on line %zu\n\n\e[0m",
		p->curr_field_name, p->parsing_id, p->line_count + 1);
	print_declaration_hint(p->parsing_id[0]);
}

void	print_parsing_error(t_parsing *p)
{
	printf("\e[1;31mError\n\e[0m");
	if (p->parsing_err == UNKNOWN_ELEMENT_ERR)
		print_unknown_element_error(p);
	else if (p->parsing_err == INVALID_FIELD_ERR)
		print_invalid_field_error(p);
	else if (p->parsing_err == MISSING_FIELD_ERR)
		print_missing_field_error(p);
	else if (p->parsing_err == EXTRA_FIELD_ERR)
		print_extra_field_error(p);
	else if (p->parsing_err == MULTI_DEF_ERR)
		print_multi_def_error(p);
	else if (p->parsing_err == OUT_OF_RANGE_ERR)
		print_out_of_range_error(p);
}
