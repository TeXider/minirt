/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:25:13 by almighty          #+#    #+#             */
/*   Updated: 2026/06/13 14:58:34 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static int	destroy_hook(void *mlx_ptr)
{
	mlx_loop_end(mlx_ptr);
	return (0);
}

static int	esc_hook(int keycode, void *mlx_ptr)
{
	if (keycode == 65307)
		mlx_loop_end(mlx_ptr);
	return (0);
}

bool	init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		env->err = MLX_INIT_ERR;
		return (true);
	}
	env->mlx_win = mlx_new_window(env->mlx, WIN_X, WIN_Y, env->file_name);
	if (!env->mlx_win)
	{
		env->err = MLX_INIT_ERR;
		return (true);
	}
	env->img.img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
	if (!env->img.img)
	{
		env->err = MLX_INIT_ERR;
		return (true);
	}
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel,
			&env->img.line_length, &env->img.endian);
	mlx_hook(env->mlx_win, 17, 0, destroy_hook, env->mlx);
	mlx_hook(env->mlx_win, 2, 1, esc_hook, env->mlx);
	return (false);
}

void	put_pixel_to_img(t_img *img, int x, int y, t_color *color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = (color->r << 16) + (color->g << 8) + color->b;
}
