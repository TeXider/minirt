/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 21:51:19 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 18:30:15 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

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
		init_hooks(&env);
		render_image(&env);
		mlx_loop(env.mlx);
	}
	clean_exit(&env);
}
