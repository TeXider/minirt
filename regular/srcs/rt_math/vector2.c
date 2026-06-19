/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:27:56 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/19 12:16:42 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

inline float	vector_dot_prod(t_vector v, t_vector u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

inline float	vector_square(t_vector v)
{
	return (vector_dot_prod(v, v));
}

inline float	vector_norm(t_vector v)
{
	return (sqrt(vector_square(v)));
}
