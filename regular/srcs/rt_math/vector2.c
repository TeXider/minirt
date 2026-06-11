/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:27:56 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/11 12:55:10 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

inline float	vector_square(t_vector *v)
{
	return (vector_dot_prod(v, v));
}

inline float	vector_norm(t_vector *v)
{
	return (sqrt(vector_square(v)));
}

inline void	vector_normalize(t_vector *v)
{
	float	norm;

	norm = vector_norm(v);
	if (!norm)
		*v = (t_vector) {1, 0, 0};
	else
		*v = vector_scale(v, 1 / vector_norm(v));
}
