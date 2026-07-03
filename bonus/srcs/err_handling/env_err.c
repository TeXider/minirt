/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:59:52 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/01 13:14:09 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static void	print_io_err(t_env *env)
{
	if (env->err == OPEN_ERR)
	{
		perror("open() function error:\e[0m");
		printf("\n\n\e[1mⓘ\e[0m    *Why do you look at me like its my fault?"
			"\n\n");
	}
	else
	{
		perror("Fatal malloc() function error:\e[0m");
		printf("\n\n\e[1mⓘ\e[0m    Do you want me to fail that bad?\n\n");
	}
}

void	print_error(t_env *env)
{
	if (!env->err)
		return ;
	printf("\e[1;31mError\n\e[0m\e[1m↳ ");
	if (env->err == INVALID_ARG_COUNT_ERR)
		printf("./minirt : Invalid number of arguments\n\n"
			"ⓘ\e[0m   Usage: ./minirt [rt_scene_path] (File must end with .rt)"
			"\e[0m\n\n");
	else if (env->err == MLX_INIT_ERR)
		printf("MiniLibX failed to initiate\n\n"
			"ⓘ\e[0m    Oh... well... there's nothing we can do\e[0m\n\n");
	else if (env->err == MISSING_FIELD_ERR)
		printf("./minirt : Invalid file extension\n\n"
			"ⓘ\e[0m   Add \".rt\" at to the end of the file name\e[0m\n\n");
	else if (env->err == MALLOC_ERR)
	{
		perror("Fatal malloc() function error:\e[0m");
		printf("\n\n\e[1mⓘ\e[0m    *chuckles* I'm in danger\n\n");
	}
	else
		print_io_err(env);
}
