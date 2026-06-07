/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:20:42 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 18:26:02 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

bool	check_file_extension(char *file_name, t_env *env)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (i > 2 && file_name[i - 3] == '.' && file_name[i - 2] == 'r'
		&& file_name[i - 1] == 't')
		return (false);
	env->err = INVALID_FILE_EXTENSION_ERR;
	return (true);
}

bool	init_env(t_env *env, char *file_name)
{
	env->mlx = NULL;
	env->mlx_win = NULL;
	env->img.img = NULL;
	env->file_name = file_name;
	env->vis_env.has_cam = false;
	env->vis_env.has_alight = false;
	env->vis_env.has_light = false;
	env->vis_env.planes = malloc(sizeof(t_plane) *  8);
	env->vis_env.spheres = malloc(sizeof(t_plane) *  8);
	env->vis_env.cylinders = malloc(sizeof(t_plane) *  8);
	if (!env->vis_env.planes || !env->vis_env.spheres
		|| !env->vis_env.cylinders)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	env->vis_env.planes_len = 0;
	env->vis_env.spheres_len = 0;
	env->vis_env.cylinders_len = 0;
	env->err = 0;
	return (check_file_extension(env, file_name));
}