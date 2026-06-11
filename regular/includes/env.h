/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:09:58 by almighty          #+#    #+#             */
/*   Updated: 2026/06/08 21:48:00 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include <stdio.h>
# include "../../mlx_linux/mlx.h"
# include "rt_math.h"

# define WIN_X	1280
# define WIN_Y	720

// VISUAL ENV

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
	bool		has_alight;
	bool		has_light;
	t_plane		*planes;
	size_t		planes_len;
	t_sphere	*spheres;
	size_t		spheres_len;
	t_cylinder	*cylinders;
	size_t		cylinders_len;
}	t_visual_env;

// ENV

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_env
{
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	char			*file_name;
	t_visual_env	vis_env;
	int				err;
}	t_env;

bool	init_env(t_env *env, char *file_name);

#endif