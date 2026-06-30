/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:23:29 by almighty          #+#    #+#             */
/*   Updated: 2026/06/08 21:57:36 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

void	safe_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

bool	challoc(char **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(char) * (len + 1));
	if (!*dst)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	(*dst)[0] = '\0';
	(*dst)[len] = '\0';
	return (false);
}
