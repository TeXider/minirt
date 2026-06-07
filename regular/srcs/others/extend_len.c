/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:17:47 by almighty          #+#    #+#             */
/*   Updated: 2026/06/04 21:51:31 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../includes/env.h"

static bool	safe_alloc(void **dst, size_t size)
{
	*dst = malloc(size);
	if (!*dst)
	{
		print_error(MALLOC_ERR, NULL);
		return (true);
	}
	return (false);
}

bool	extend_planes_len(t_visual_env *v_env)
{
	t_plane	*tmp;
	size_t	i;

	if (safe_alloc(&v_env->planes, sizeof(t_plane) * (v_env->planes_len + 8)))
		return (true);
	i = 0;
	while (i < v_env->planes_len)
	{
		tmp[i] = v_env->planes[i];
		i++;
	}
	free(v_env->planes);
	v_env->planes = tmp;
	return (false);
}

bool	extend_spheres_len(t_visual_env *v_env)
{
	t_sphere	*tmp;
	size_t		i;

	if (safe_alloc(&v_env->spheres,
			sizeof(t_sphere) * (v_env->spheres_len + 8)))
		return (true);
	i = 0;
	while (i < v_env->spheres_len)
	{
		tmp[i] = v_env->spheres[i];
		i++;
	}
	free(v_env->spheres);
	v_env->spheres = tmp;
	return (false);
}

bool	extend_cylinders_len(t_visual_env *v_env)
{
	t_cylinder	*tmp;
	size_t		i;

	if (safe_alloc(&v_env->cylinders,
		sizeof(t_cylinder) * (v_env->cylinders_len + 8)))
		return (true);
	i = 0;
	while (i < v_env->cylinders_len)
	{
		tmp[i] = v_env->cylinders[i];
		i++;
	}
	free(v_env->cylinders);
	v_env->cylinders = tmp;
	return (false);
}
