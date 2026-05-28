/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:45:48 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/27 17:42:35 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include <stdbool.h>
# include "../includes/vector.h"
# include "../includes/ray.h"
# include "../includes/others.h"

typedef struct s_plane
{
	t_vector	o;
	t_vector	n;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_vector	o;
	float		d;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	o;
	t_vector	n;
	float		d;
	float		h;
	t_color		color;
}	t_cylinder;

bool		get_plane_intersection(t_plane *plane, t_ray *ray, t_vector *res);
bool		get_sphere_intersection(t_sphere *sphere, t_ray *ray,
				t_vector *res);
bool		get_sphere_intersection2(t_sphere *sphere, t_ray *ray,
				t_vector *res);
bool		get_cylinder_intersection(t_cylinder *cylinder, t_ray *ray,
				t_vector *res);
bool		get_cylinder_intersection2(t_cylinder *cylinder, t_ray *ray,
				t_vector *res);

t_vector	sphere_surface_norm_vector(t_sphere *sphere, t_vector *point);
t_vector	cylinder_surface_norm_vector(t_cylinder *cylinder, t_vector *point);

#endif