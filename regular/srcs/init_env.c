/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:20:42 by almighty          #+#    #+#             */
/*   Updated: 2026/06/02 16:08:18 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

static bool	init_mlx(t_env *env, char *filename)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		print_error(MLX_INIT_ERR_MSG, MLX_INIT_ERR_HINT, env);
		return (true);
	}
	env->mlx_win = mlx_new_window(env->mlx, WIN_X, WIN_Y, filename);
	if (!env->mlx_win)
	{
		print_error(MLX_INIT_ERR_MSG, MLX_INIT_ERR_HINT, env);
		return (true);
	}
	env->img.img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
	if (!env->img.img)
	{
		print_error(MLX_INIT_ERR_MSG, MLX_INIT_ERR_HINT, env);
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
	set_culprit1(filename, env);
	print_error(INVALID_FILE_EXTENSION, NULL, env);
	return (true);
}

static void	clean_garbage(t_env *env)
{
	env->mlx = NULL;
	env->mlx_win = NULL;
	env->img.img = NULL;
	env->vis_env.has_cam = false;
	env->vis_env.has_alight = false;
	env->vis_env.has_light = false;
	env->vis_env.planes = NULL;
	env->vis_env.planes_len = 0;
	env->vis_env.spheres = NULL;
	env->vis_env.spheres_len = 0;
	env->vis_env.cylinders = NULL;
	env->vis_env.cylinders_len = 0;
}

bool	init_env(t_env *env, char *filename)
{
	clean_garbage(env);
	return (check_file_extension(filename, env)
		|| parse_file(filename, env)
		|| init_mlx(filename, env));
}