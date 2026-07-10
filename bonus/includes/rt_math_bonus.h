/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:00:58 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:30:09 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include <stdbool.h>
# include "image_bonus.h"
# include "others_bonus.h"

# define PI 3.1415926f

typedef struct s_rt_screen	t_rt_screen;
typedef struct s_img		t_img;

void		render_image(t_env *env);

// VECTORS

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

t_vector	vector_scale(t_vector v, float k);
t_vector	vector_add(t_vector v, t_vector u);
t_vector	vector_sub(t_vector v, t_vector u);
t_vector	vector_normalize(t_vector v);
float		vector_dot_prod(t_vector v, t_vector u);
float		vector_square(t_vector v);
float		vector_norm(t_vector v);

// RAYS

typedef struct s_ray
{
	t_vector	o;
	t_vector	n;
}	t_ray;

void		ray_trace_aa(t_rt_screen *rt_s, t_color *dst_color,
				t_visual_env *v_env);
void		ray_trace(t_ray *r, t_color *dst_color, t_visual_env *v_env);
t_vector	point_on_ray(t_ray *r, float t);

// SHAPES

typedef struct s_plane
{
	t_vector	o;
	t_vector	n;
	t_vector	e_y;
	t_vector	e_z;
	t_color		color;
	float		check;
	t_img		bump;
	t_img		txt;
}	t_plane;

typedef struct s_sphere
{
	t_vector	o;
	float		r;
	t_color		color;
	int			check;
	t_img		bump;
	t_img		txt;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	o;
	t_vector	n;
	t_vector	e_y;
	t_vector	e_z;
	float		r;
	float		h;
	t_color		color;
	int			check;
	t_img		bump;
	t_img		txt;
}	t_cylinder;

typedef struct s_cone
{
	t_vector	o;
	t_vector	n;
	t_vector	e_y;
	t_vector	e_z;
	float		a;
	float		h;
	t_color		color;
	float		tan_a;
	float		inter_k;
	int			check;
	t_img		bump;
	t_img		txt;
}	t_cone;

# define TPLANE		'p'
# define TSPHERE	's'
# define TCYLINDER	'c'
# define TCONE		'k'

typedef struct s_intersection
{
	float		distance;
	t_vector	p;
	t_vector	surf_n;
	void		*shape;
	t_color		color;
	float		x_img_comp;
	float		y_img_comp;
}	t_intersection;

bool		get_plane_intersection(t_plane *plane, t_ray *ray,
				t_intersection *dst);
bool		get_sphere_intersection(t_sphere *sphere, t_ray *ray,
				t_intersection *dst);
bool		get_cylinder_intersection(t_cylinder *cylinder, t_ray *ray,
				t_intersection *dst);
bool		get_cone_intersection(t_cone *cone, t_ray *ray,
				t_intersection *dst);

bool		get_cylinder_top_intersection(t_cylinder *cy, t_ray *r,
				t_intersection *dst);
bool		get_cone_top_intersection(t_cone *co, t_ray *r, float n_dot_r,
				t_intersection *dst);

bool		is_in_shadow(t_ray *light_r, float dis_to_light, void *shape,
				t_visual_env *v_env);

typedef struct s_pol_coef
{
	float	a;
	float	b;
	float	c;
}	t_pol_coef;

bool		solve_pol_coef(t_pol_coef *pc, float *res);
float		sign(float n);
void		compute_basis(t_vector n, t_vector *e_y, t_vector *e_z);
float		numerical_min(float a, float b);

t_color		txt_color(float x_comp, float y_comp, t_img *img);
float		txt_intensity(float x_comp, float y_comp, t_img *img);
t_color		sky_box_color(t_ray *r, t_img *txt);

typedef struct s_top
{
	t_vector	o;
	t_vector	n;
	t_vector	e_y;
	t_vector	e_z;
	float		r;
	void		*shape;
	float		h_max;
	int			check;
	t_img		*bump;
	t_img		*txt;
	t_color		color;
}	t_top;

void		set_plane_inter_vals(t_plane *pl, t_ray *r, t_intersection *dst);
void		set_sphere_inter_vals(t_sphere *sp, t_ray *r, t_intersection *dst);
void		set_top_inter_vals(t_top *t, float h, t_ray *r,
				t_intersection *dst);
void		set_cylinder_inter_vals(t_cylinder *cy, t_ray *r,
				t_intersection *dst);
void		set_cone_inter_vals(t_cone *co, t_ray *r, t_intersection *dst);

t_color		plane_color(t_plane *p, t_intersection *inter);
t_color		point_color(int check, t_img *txt, t_color c,
				t_intersection *inter);
t_color		inv_color(t_color c, bool inv);

void		compute_bump_comp(float bc[2], t_img *bump, t_intersection *inter);
t_vector	plane_surf_n(t_plane *pl, t_intersection *inter);
t_vector	sphere_surf_n(t_sphere *sp, t_intersection *inter);
t_vector	cylinder_surf_n(t_cylinder *cy, t_intersection *inter);
t_vector	top_surf_n(t_top *t, t_intersection *inter);
t_vector	cone_surf_n(t_cone *co, t_intersection *inter);

#endif