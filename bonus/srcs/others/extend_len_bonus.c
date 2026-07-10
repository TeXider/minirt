/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_len_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:17:47 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:30:40 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../includes/env_bonus.h"

bool	extend_planes_len(t_env *env)
{
	t_plane	*tmp;
	size_t	i;

	tmp = malloc(sizeof(t_plane) * (env->vis_env.planes_count + 8));
	if (!tmp)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	i = 0;
	while (i < env->vis_env.planes_count)
	{
		tmp[i] = env->vis_env.planes[i];
		i++;
	}
	free(env->vis_env.planes);
	env->vis_env.planes = tmp;
	return (false);
}

bool	extend_spheres_len(t_env *env)
{
	t_sphere	*tmp;
	size_t		i;

	tmp = malloc(sizeof(t_sphere) * (env->vis_env.spheres_count + 8));
	if (!tmp)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	i = 0;
	while (i < env->vis_env.spheres_count)
	{
		tmp[i] = env->vis_env.spheres[i];
		i++;
	}
	free(env->vis_env.spheres);
	env->vis_env.spheres = tmp;
	return (false);
}

bool	extend_cylinders_len(t_env *env)
{
	t_cylinder	*tmp;
	size_t		i;

	tmp = malloc(sizeof(t_cylinder) * (env->vis_env.cylinders_count + 8));
	if (!tmp)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	i = 0;
	while (i < env->vis_env.cylinders_count)
	{
		tmp[i] = env->vis_env.cylinders[i];
		i++;
	}
	free(env->vis_env.cylinders);
	env->vis_env.cylinders = tmp;
	return (false);
}

bool	extend_lights_len(t_env *env)
{
	t_light	*tmp;
	size_t	i;

	tmp = malloc(sizeof(t_light) * (env->vis_env.lights_count + 8));
	if (!tmp)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	i = 0;
	while (i < env->vis_env.lights_count)
	{
		tmp[i] = env->vis_env.lights[i];
		i++;
	}
	free(env->vis_env.lights);
	env->vis_env.lights = tmp;
	return (false);
}

bool	extend_cones_len(t_env *env)
{
	t_cone	*tmp;
	size_t	i;

	tmp = malloc(sizeof(t_cone) * (env->vis_env.cones_count + 8));
	if (!tmp)
	{
		env->err = MALLOC_ERR;
		return (true);
	}
	i = 0;
	while (i < env->vis_env.cones_count)
	{
		tmp[i] = env->vis_env.cones[i];
		i++;
	}
	free(env->vis_env.cones);
	env->vis_env.cones = tmp;
	return (false);
}
