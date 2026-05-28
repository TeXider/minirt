/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:27:56 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/27 17:47:34 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/vector.h"

inline float	vector_square(t_vector *v)
{
	return (vector_dot_product(v, v));
}

inline float	vector_norm(t_vector *v)
{
	return (sqrt(vector_square(v)));
}
