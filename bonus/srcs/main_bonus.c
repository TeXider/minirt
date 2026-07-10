/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 21:51:19 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:32:21 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env_bonus.h"
#include "../includes/parsing_bonus.h"

static void	destroy_shapes_imgs2(t_visual_env *v_env)
{
	size_t	i;

	i = -1;
	while (++i < v_env->cylinders_count)
	{
		if (v_env->cylinders[i].bump.img)
			mlx_destroy_image(v_env->env->mlx, v_env->cylinders[i].bump.img);
		if (v_env->cylinders[i].txt.img)
			mlx_destroy_image(v_env->env->mlx, v_env->cylinders[i].txt.img);
	}
	i = -1;
	while (++i < v_env->cones_count)
	{
		if (v_env->cones[i].bump.img)
			mlx_destroy_image(v_env->env->mlx, v_env->cones[i].bump.img);
		if (v_env->cones[i].txt.img)
			mlx_destroy_image(v_env->env->mlx, v_env->cones[i].txt.img);
	}
}

static void	destroy_shapes_imgs(t_visual_env *v_env)
{
	size_t	i;

	i = -1;
	while (++i < v_env->planes_count)
	{
		if (v_env->planes[i].bump.img)
			mlx_destroy_image(v_env->env->mlx, v_env->planes[i].bump.img);
		if (v_env->planes[i].txt.img)
			mlx_destroy_image(v_env->env->mlx, v_env->planes[i].txt.img);
	}
	i = -1;
	while (++i < v_env->spheres_count)
	{
		if (v_env->spheres[i].bump.img)
			mlx_destroy_image(v_env->env->mlx, v_env->spheres[i].bump.img);
		if (v_env->spheres[i].txt.img)
			mlx_destroy_image(v_env->env->mlx, v_env->spheres[i].txt.img);
	}
	destroy_shapes_imgs2(v_env);
}

static void	clean_exit(t_env *env)
{
	free(env->vis_env.lights);
	destroy_shapes_imgs(&env->vis_env);
	free(env->vis_env.planes);
	free(env->vis_env.spheres);
	free(env->vis_env.cylinders);
	free(env->vis_env.cones);
	if (env->img.img)
		mlx_destroy_image(env->mlx, env->img.img);
	if (env->vis_env.sky_box.img)
		mlx_destroy_image(env->mlx, env->vis_env.sky_box.img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	free(env->mlx);
	exit(env->err != NO_ERR);
}

static bool	check_args(int argc, char **argv, t_env *env)
{
	int	i;

	if (argc != 2)
	{
		env->err = INVALID_ARG_COUNT_ERR;
		return (true);
	}
	i = 0;
	while (argv[1][i])
		i++;
	if (i > 2 && argv[1][i - 3] == '.' && argv[1][i - 2] == 'r'
		&& argv[1][i - 1] == 't')
		return (false);
	env->err = INVALID_FILE_EXTENSION_ERR;
	return (true);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (check_args(argc, argv, &env))
	{
		print_error(&env);
		exit(1);
	}
	if (init_env(&env, argv[1])
		|| parse_file(&env)
		|| init_mlx(&env))
		print_error(&env);
	else
	{
		printf("Rendering...\n");
		render_image(&env);
		mlx_put_image_to_window(env.mlx, env.mlx_win, env.img.img, 0, 0);
		printf("Rendering over\n");
		mlx_loop(env.mlx);
	}
	clean_exit(&env);
}
