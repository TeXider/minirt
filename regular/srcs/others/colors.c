/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:58:32 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 10:22:03 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_color	scale_color(t_color c, float k)
{
	float	tmp;

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
	c.r *= k;
	c.g *= k;
	c.b *= k;
	return (c);
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
