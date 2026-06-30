/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:01:38 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 14:29:54 by almighty         ###   ########.fr       */
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

static void	print_out_of_range_error(t_parsing *p)
{
	printf("\e[1;31mError\n\e[0m");
	printf("↳ \e[1mField '\e[3m%s\e[23m' (\"%.*s\") is out-of-range for %s "
		"on line %zu\e[0m\n\n", p->curr_field_name,
		field_len(p->line + p->curr_field_i),
		p->line + p->curr_field_i, p->parsing_id,
		p->line_count + 1);
}

static void	print_multi_def_error(t_parsing *p)
{
	printf("\e[1;31mError\n\e[0m");
	printf("↳ \e[1mExtraneous %s definition on line %zu\e[0m\n\n", p->parsing_id,
		p->line_count + 1);
	printf("\e[1mⓘ\e[0;3m   There can only be one definition for %s (%c) in a"
		" .rt scene\e[0m\n\n", p->parsing_id, p->parsing_id[0]);
}

static void	print_extra_field_error(t_parsing *p)
{
	printf("\e[1;31mError\n\e[0m");
	printf("↳ \e[1mExtra field '\e[3m%.*s\e[23m' for %s on line %zu\e[0m\n\n",
		field_len(p->line + p->curr_field_i), p->line + p->curr_field_i,
		p->parsing_id, p->line_count + 1);
}

static void	print_missing_field_error(t_parsing *p)
{
	printf("\e[1;31mError\n\e[0m");
	printf("↳ \e[1mMissing field '\e[3m%s\e[23m' for %s on line %zu\n\n\e[0m",
		p->curr_field_name, p->parsing_id, p->line_count + 1);
}

static void	print_invalid_field_error(t_parsing *p)
{
	printf("\e[1;31mError\n\e[0m");
	printf("\e[1m↳ Invalid field '\e[3m%s\e[23m' (\"%.*s\")"
		" for %s on line %zu\n\n\e[0m",
		p->curr_field_name, field_len(p->line + p->curr_field_i),
		p->line + p->curr_field_i, p->parsing_id,
		p->line_count + 1);
}

static void	print_unknown_element_error(t_parsing *p)
{
	printf("\e[1;31mError\n\e[0m");
	printf("↳ Unknown element '\e[1m%.*s\e[0m' on line %zu\n\n",
		field_len(p->line + p->curr_field_i), p->line + p->curr_field_i,
		p->line_count + 1);
	printf("\e[1mⓘ\e[0;3m   Possible identifiers are A (alight), C (camera),"
		" L (light), pl (plane), sp (sphere) and cy (cylinder)\e[0m\n\n");
}

void	print_parsing_error(t_parsing *p)
{
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

void	print_error(t_env *env)
{
	printf("Ouch ouch ouch: %d\n", env->err);
}
