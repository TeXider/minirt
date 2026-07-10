/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:32:58 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:32:13 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env_bonus.h"

inline bool	solve_pol_coef(t_pol_coef *pc, float *res)
{
	float	d;

	d = pc->b * pc->b - 4.0f * pc->a * pc->c;
	if (d < 0)
		return (false);
	d = sqrtf(d);
	if (-pc->b < -d)
		return (false);
	*res = (-pc->b + d * (1 - 2 * (-pc->b >= d))) / (2.0f * pc->a);
	return (true);
}

inline t_vector	point_on_ray(t_ray *r, float t)
{
	return (vector_add(r->o, vector_scale(r->n, t)));
}

inline float	sign(float n)
{
	return (1 - 2 * (n < 0));
}

inline void	compute_basis(t_vector n, t_vector *e_y, t_vector *e_z)
{
	float	cos_theta;

	cos_theta = sqrt(1.0f - n.z * n.z);
	if (!cos_theta)
	{
		*e_z = (t_vector){0, 1, 0};
		*e_y = (t_vector){-1, 0, 0};
	}
	else
	{
		*e_z = (t_vector){-n.y / cos_theta, n.x / cos_theta, 0};
		*e_y = (t_vector){-n.x * n.z / cos_theta,
			-n.y * n.z / cos_theta, cos_theta};
	}
}

inline float	numerical_min(float a, float b)
{
	return (a + (b - a) * (b * sign(b) < a * sign(a)));
}
