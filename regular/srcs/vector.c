/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:27:56 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/27 17:47:40 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/vector.h"

inline void	init_vector(t_vector *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

inline t_vector	vector_scale(t_vector *v, float k)
{
	return ((t_vector){k * v->x, k * v->y, k * v->z});
}

inline t_vector	vector_add(t_vector *v, t_vector *u)
{
	return ((t_vector){v->x + u->x, v->y + u->y, v->z + u->z});
}

inline t_vector	vector_substract(t_vector *v, t_vector *u)
{
	return ((t_vector){v->x - u->x, v->y - u->y, v->z - u->z});
}

inline float	vector_dot_product(t_vector *v, t_vector *u)
{
	return (v->x * u->x + v->y * u->y + v->z * u->z);
}
