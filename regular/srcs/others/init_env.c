/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:20:42 by almighty          #+#    #+#             */
/*   Updated: 2026/06/12 13:25:28 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

bool	init_env(t_env *env, char *file_name)
{
	env->mlx = NULL;
	env->mlx_win = NULL;
	env->img.img = NULL;
	env->file_name = file_name;
	env->vis_env.has_cam = false;
	env->vis_env.has_alight = false;
	env->vis_env.has_light = false;
	env->vis_env.planes = malloc(sizeof(t_plane) * 8);
	env->vis_env.spheres = malloc(sizeof(t_sphere) * 8);
	env->vis_env.cylinders = malloc(sizeof(t_cylinder) * 8);
	if (!env->vis_env.planes || !env->vis_env.spheres
		|| !env->vis_env.cylinders)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	env->vis_env.planes_count = 0;
	env->vis_env.spheres_count = 0;
	env->vis_env.cylinders_count = 0;
	env->err = NO_ERR;
	return (false);
}
