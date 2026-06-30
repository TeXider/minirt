/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:09:58 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 10:49:31 by almighty         ###   ########.fr       */
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

# define V_FOV	2.095f

typedef struct s_camera
{
	t_vector	o;
	t_vector	n;
	float		h_fov;
	t_vector	e_y;
	t_vector	e_z;
}	t_camera;

typedef struct s_alighting
{
	float	intensity;
	t_color	color;
}	t_alighting;

typedef struct s_light
{
	t_vector	o;
	float		intensity;
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
	size_t		planes_count;
	t_sphere	*spheres;
	size_t		spheres_count;
	t_cylinder	*cylinders;
	size_t		cylinders_count;
}	t_visual_env;

typedef struct s_rt_screen
{
	int			pix_x;
	int			pix_y;
	t_vector	sweep;
	t_vector	y_sweep;
	t_vector	dy_sweep;
	t_vector	init_x_sweep;
	t_vector	dx_sweep;
}	t_rt_screen;

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

bool	init_mlx(t_env *env);
void	put_pixel_to_img(t_img *img, int x, int y, t_color *color);

// DEBUG

void	print_vector(t_vector *v, char *name, bool nl);
void	print_color(t_color *c, char *name, bool nl);
void	print_float(float n, char *name, bool nl);
void	print_int(int n, char *name, bool nl);

#endif