/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:25:13 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 20:21:46 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

bool	init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		print_error(MLX_INIT_ERR, NULL);
		return (true);
	}
	env->mlx_win = mlx_new_window(env->mlx, WIN_X, WIN_Y, env->file_name);
	if (!env->mlx_win)
	{
		print_error(MLX_INIT_ERR, NULL);
		return (true);
	}
	env->img.img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
	if (!env->img.img)
	{
		print_error(MLX_INIT_ERR, NULL);
		return (true);
	}
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel,
								&env->img.line_length, &env->img.endian);
	return (false);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}