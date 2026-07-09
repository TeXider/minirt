/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:09:58 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 09:28:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include <stdio.h>
# include "../../mlx_linux/mlx.h"
# include "image.h"
# include "rt_math.h"

# define WIN_X	1280
# define WIN_Y	720

// VISUAL ENV

typedef struct s_camera
{
	t_vector	o;
	t_vector	n;
	float		h_fov;
	t_vector	e_y;
	t_vector	e_z;
	int			r_x;
	int			r_y;
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
	t_color		color;
}	t_light;

typedef struct s_visual_env
{
	t_camera	cam;
	t_alighting	alight;
	bool		has_cam;
	bool		has_alight;
	t_light		*lights;
	size_t		lights_count;
	t_plane		*planes;
	size_t		planes_count;
	t_sphere	*spheres;
	size_t		spheres_count;
	t_cylinder	*cylinders;
	size_t		cylinders_count;
	t_cone		*cones;
	size_t		cones_count;
	int			aa;
	t_vector	init_dx_aa;
	t_vector	init_dy_aa;
	t_vector	dx_aa;
	t_vector	dy_aa;
	t_img		sky_box;
	t_env		*env;
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
bool	open_xpm(t_img *dst, char *filename, t_env *env);

// DEBUG

void	print_vector(t_vector *v, char *name, bool nl);
void	print_color(t_color *c, char *name, bool nl);
void	print_float(float n, char *name, bool nl);
void	print_int(int n, char *name, bool nl);

#endif