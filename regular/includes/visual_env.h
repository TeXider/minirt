/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:07:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/02 12:11:00 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_ENV_H
# define VISUAL_ENV_H

# include <stdbool.h>
# include "vector.h"
# include "others.h"

typedef struct s_camera
{
	t_vector	o;
	t_vector	n;
	int			h_fov;
}	t_camera;

typedef struct s_alighting
{
	float	intensity;
	t_color	color;
}	t_alighting;

typedef struct s_light
{
	t_vector	o;
	float		brightness;
}	t_light;

typedef struct s_visual_env
{
	t_camera	cam;
	t_alighting	alight;
	t_light		light;
	bool		has_cam;
}	t_visual_env;

#endif