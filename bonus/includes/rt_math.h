/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:00:58 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 11:19:46 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include <stdbool.h>
# include "others.h"

# define PI 3.1415926f

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

void		ray_trace(t_ray *r, t_color *dst_color, t_visual_env *v_env);
t_vector	point_on_ray(t_ray *r, float t);

// SHAPES

typedef struct s_plane
{
	t_vector	o;
	t_vector	n;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_vector	o;
	float		r;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	o;
	t_vector	n;
	float		r;
	float		h;
	t_color		color;
}	t_cylinder;

# define TPLANE		'p'
# define TSPHERE	's'
# define TCYLINDER	'c'

typedef struct s_intersection
{
	float		distance;
	t_vector	p;
	t_vector	surf_n;
	void		*shape;
	char		type;
	t_color		color;
}	t_intersection;

bool		get_plane_intersection(t_plane *plane, t_ray *ray,
				t_intersection *dst);
bool		get_sphere_intersection(t_sphere *sphere, t_ray *ray,
				t_intersection *dst);
bool		get_cylinder_intersection(t_cylinder *cylinder, t_ray *ray,
				t_intersection *dst);

typedef struct s_pol_coef
{
	float	a;
	float	b;
	float	c;
}	t_pol_coef;

bool		solve_pol_coef(t_pol_coef *pc, float *res);
float		sign(float n);

#endif