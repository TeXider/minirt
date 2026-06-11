/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:17:47 by almighty          #+#    #+#             */
/*   Updated: 2026/06/11 21:17:45 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../includes/env.h"

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
