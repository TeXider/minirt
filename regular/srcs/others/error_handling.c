/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:01:38 by almighty          #+#    #+#             */
/*   Updated: 2026/06/11 20:47:26 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_parsing_error(t_parsing *p)
{
	printf("Ouch: %d (%s), \"%s\" -> %zu:'%s', %zu:'%s'\n", p->parsing_err, p->curr_field_name, p->line, p->curr_field_i, p->line + p->curr_field_i, p->line_i, p->line + p->line_i);
}

void	print_error(t_env *env)
{
	printf("Ouch ouch ouch: %d\n", env->err);
}