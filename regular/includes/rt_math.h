/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:00:58 by almighty          #+#    #+#             */
/*   Updated: 2026/06/19 11:27:11 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include <stdbool.h>
# include "others.h"

# define PI 3.1415926f

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

t_vector	point_on_ray(t_ray *ray, float t);

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

bool		get_plane_intersection(t_plane *plane, t_ray *ray, float *res);
bool		get_sphere_intersection(t_sphere *sphere, t_ray *ray,
				float *res);
// bool		get_cylinder_intersection(t_cylinder *cylinder, t_ray *ray,
// 				float *res);

t_vector	sphere_surface_norm_vector(t_sphere *sphere, t_vector *point);
t_vector	cylinder_surface_norm_vector(t_cylinder *cylinder, t_vector *point);

typedef struct s_pol_coef
{
	float	a;
	float	b;
	float	c;
}	t_pol_coef;

#endif