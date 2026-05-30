/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:45:48 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/30 11:31:41 by almighty         ###   ########.fr       */
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
	float		r;
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

bool		get_plane_intersection(t_plane *plane, t_ray *ray, float *res);
bool		get_sphere_intersection(t_sphere *sphere, t_ray *ray,
				float *res);
bool		get_cylinder_intersection(t_cylinder *cylinder, t_ray *ray,
				float *res);

t_vector	sphere_surface_norm_vector(t_sphere *sphere, t_vector *point);
t_vector	cylinder_surface_norm_vector(t_cylinder *cylinder, t_vector *point);

#endif