/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:23:18 by almighty          #+#    #+#             */
/*   Updated: 2026/07/08 22:43:52 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/rt_math.h"

t_color	inv_color(t_color c, bool inv)
{
	if (inv)
	{
		c.r = 255 - c.r;
		c.g = 255 - c.g;
		c.b = 255 - c.b;
	}
	return (c);
}

t_color	plane_color(t_plane *pl, t_intersection *inter)
{
	int		check_x;
	int		check_y;
	float	mod_x;
	float	mod_y;

	if (!pl->check && !pl->txt.img)
		return (pl->color);
	mod_x = fmodf(inter->x_img_comp, 1);
	mod_y = fmodf(inter->y_img_comp, 1);
	mod_x += (inter->x_img_comp < 0);
	mod_y += (inter->y_img_comp < 0);
	if (pl->txt.img)
		return (txt_color(mod_x, mod_y, &pl->txt));
	check_x = floorf(inter->x_img_comp);
	check_y = floorf(inter->y_img_comp);
	return (inv_color(pl->color, (check_x + check_y) & 1));
}

t_color	point_color(int check, t_img *txt, t_color c, t_intersection *inter)
{
	int		check_x;
	int		check_y;

	if (!check && !txt->img)
		return (c);
	if (txt->img)
		return (txt_color(inter->x_img_comp, inter->y_img_comp, txt));
	check_x = check * inter->y_img_comp;
	check_y = check * inter->x_img_comp;
	return (inv_color(c, (check_x + check_y) & 1));
}
