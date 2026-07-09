/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 14:26:24 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 01:44:40 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

static t_color	image_color(t_img *img, int x, int y)
{
	int		c;
	char	*pixel;

	x *= 1 - (x < 0);
	x += (img->width - x) * (x >= img->width);
	y *= 1 - (y < 0);
	y += (img->width - y) * (y >= img->height);
	pixel = img->addr + y * img->line_length + x * (img->bits_per_pixel / 8);
	c = *(int *)pixel;
	return ((t_color){(c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF});
}

inline t_color	txt_color(float x_comp, float y_comp, t_img *img)
{
	return (image_color(img, x_comp * img->width, y_comp * img->height));
}

inline float	txt_intensity(float x_comp, float y_comp, t_img *img)
{
	t_color	c;

	c = txt_color(x_comp, y_comp, img);
	return (c.r / 765.0f + c.g / 765.0f + c.b / 765.0f);
}
