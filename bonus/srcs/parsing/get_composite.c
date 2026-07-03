/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_composite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 20:02:50 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 11:45:43 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	get_vector(t_vector *dst, float range[2], t_parsing *p)
{
	return (get_float(&dst->x, range, true, p)
		|| get_float(&dst->y, range, true, p)
		|| get_float(&dst->z, range, false, p));
}

bool	get_color(t_color *dst, t_parsing *p)
{
	return (get_int(&dst->r, (int [2]){0, 255}, true, p)
		|| get_int(&dst->g, (int [2]){0, 255}, true, p)
		|| get_int(&dst->b, (int [2]){0, 255}, false, p));
}
