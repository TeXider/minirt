/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:17:47 by almighty          #+#    #+#             */
/*   Updated: 2026/06/02 15:28:04 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "others.h"

bool	safe_alloc(void **dst, size_t size)
{
	*dst = malloc(size);
	if (!*dst)
	{
		print_error(MALLOC_ERR, MALLOC_ERR_HINT, NULL);
		return (true);
	}
	return (false);
}

bool	safe_realloc(void **dst, size_t oldsize, size_t newsize)
{
	char	*tmp;
	size_t	i;

	if (safe_alloc(newsize, &tmp))
		return (true);
	i = 0;
	while (i < oldsize)
	{
		tmp[i] = ((char *)(*dst))[i];
		i++;
	}
	free(*dst);
	*dst = tmp;
	return (false);
}