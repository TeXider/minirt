/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:27:56 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/15 16:12:37 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

inline t_vector	vector_scale(t_vector v, float k)
{
	return ((t_vector){k * v.x, k * v.y, k * v.z});
}

inline t_vector	vector_add(t_vector v, t_vector u)
{
	return ((t_vector){v.x + u.x, v.y + u.y, v.z + u.z});
}

inline t_vector	vector_sub(t_vector v, t_vector u)
{
	return ((t_vector){v.x - u.x, v.y - u.y, v.z - u.z});
}

inline t_vector	vector_normalize(t_vector v)
{
	float	norm;

	norm = vector_norm(v);
	if (!norm)
		return ((t_vector){1, 0, 0});
	else
		return (vector_scale(v, 1.0f / norm));
}
