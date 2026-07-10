/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:58:32 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:30:38 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env_bonus.h"

t_color	scale_color(t_color c, float k)
{
	float	tmp;

	if (!k || k < 0)
		return ((t_color){0, 0, 0});
	if (c.r)
	{
		tmp = 255.0f / (float) c.r;
		if (tmp < k)
			k = tmp;
	}
	if (c.g)
	{
		tmp = 255.0f / (float) c.g;
		if (tmp < k)
			k = tmp;
	}
	if (c.b)
	{
		tmp = 255.0f / (float) c.b;
		if (tmp < k)
			k = tmp;
	}
	return ((t_color){c.r * k, c.g * k, c.b * k});
}

t_color	light_color(t_color color, t_color light)
{
	return ((t_color){color.r * light.r / 255.0f, color.g * light.g / 255.0f,
		color.b * light.b / 255.0f});
}

t_color	add_colors(t_color a, t_color b)
{
	a.r += b.r;
	if (a.r > 255)
		a.r = 255;
	a.g += b.g;
	if (a.g > 255)
		a.g = 255;
	a.b += b.b;
	if (a.b > 255)
		a.b = 255;
	return (a);
}
