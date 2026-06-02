/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 21:51:19 by almighty          #+#    #+#             */
/*   Updated: 2026/06/02 14:16:21 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
	{
		print_error(INVALID_ARG_COUNT_MSG, EXEC_HINT);
		return (1);
	}
	if (init_env(&env, argv[1]))
	{
		free_env(&env);
		return (1);
	}
	init_hooks(&env);
	mlx_loop(env.mlx);
	free_env(&env);
}
