/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:20:42 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 12:01:34 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static bool	init_vis_env(t_env *env)
{
	env->vis_env.has_cam = false;
	env->vis_env.has_alight = false;
	env->vis_env.alight.color = (t_color){0, 0, 0};
	env->vis_env.alight.intensity = 0.0f;
	env->vis_env.aa = 0;
	env->vis_env.sky_box.img = NULL;
	env->vis_env.planes = malloc(sizeof(t_plane) * 8);
	env->vis_env.spheres = malloc(sizeof(t_sphere) * 8);
	env->vis_env.cylinders = malloc(sizeof(t_cylinder) * 8);
	env->vis_env.lights = malloc(sizeof(t_cylinder) * 8);
	env->vis_env.cones = malloc(sizeof(t_cylinder) * 8);
	if (!env->vis_env.planes || !env->vis_env.spheres
		|| !env->vis_env.cylinders || !env->vis_env.lights
		|| !env->vis_env.cones)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	env->vis_env.planes_count = 0;
	env->vis_env.spheres_count = 0;
	env->vis_env.cylinders_count = 0;
	env->vis_env.lights_count = 0;
	env->vis_env.cones_count = 0;
	env->vis_env.env = env;
	return (false);
}

bool	init_env(t_env *env, char *file_name)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		env->err = MLX_INIT_ERR;
		return (true);
	}
	env->mlx_win = NULL;
	env->img.img = NULL;
	env->file_name = file_name;
	if (init_vis_env(env))
		return (true);
	env->err = NO_ERR;
	return (false);
}
