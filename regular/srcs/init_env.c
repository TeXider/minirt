/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:20:42 by almighty          #+#    #+#             */
/*   Updated: 2026/06/04 21:51:42 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

static bool	init_mlx(t_env *env, char *filename)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		print_error(MLX_INIT_ERR, NULL);
		return (true);
	}
	env->mlx_win = mlx_new_window(env->mlx, WIN_X, WIN_Y, filename);
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

static bool	check_file_extension(char *filename, t_env *env)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i > 2 && filename[i - 3] == '.' && filename[i - 2] == 'r'
		&& filename[i - 1] == 't')
		return (false);
	print_error(INVALID_FILE_EXTENSION_ERR, filename);
	return (true);
}

static bool	init_vals(t_env *env)
{
	env->mlx = NULL;
	env->mlx_win = NULL;
	env->img.img = NULL;
	env->vis_env.has_cam = false;
	env->vis_env.has_alight = false;
	env->vis_env.has_light = false;
	env->vis_env.planes = malloc(sizeof(t_plane) *  8);
	env->vis_env.spheres = malloc(sizeof(t_plane) *  8);
	env->vis_env.cylinders = malloc(sizeof(t_plane) *  8);
	if (!env->vis_env.planes || !env->vis_env.spheres
		|| !env->vis_env.cylinders)
	{
		print_error(MALLOC_ERR, NULL);
		return (true);
	}
	env->vis_env.planes_len = 0;
	env->vis_env.spheres_len = 0;
	env->vis_env.cylinders_len = 0;
	return (false);
}

bool	init_env(t_env *env, char *filename)
{
	return (init_vals(env)
		|| check_file_extension(filename, env)
		|| parse_file(filename, env)
		|| init_mlx(filename, env));
}