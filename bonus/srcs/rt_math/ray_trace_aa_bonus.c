/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace_aa_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 02:18:29 by almighty          #+#    #+#             */
/*   Updated: 2026/07/10 08:31:47 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env_bonus.h"

static t_vector	compute_aa_ray(int aa, int x, int y, t_rt_screen *rt_s)
{
	float	dx;
	float	dy;

	dx = (x + 0.5f) / aa - 0.5f;
	dy = (y + 0.5f) / aa - 0.5f;
	return (vector_normalize(vector_add(rt_s->sweep, vector_add(
					vector_scale(rt_s->dx_sweep, dx),
					vector_scale(rt_s->dy_sweep, dy)))));
}

static void	init_colors(int colors[3])
{
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
}

void	ray_trace_aa(t_rt_screen *rt_s, t_color *dst_color, t_visual_env *v_env)
{
	int		y;
	int		x;
	int		colors[3];
	float	aa2;
	t_ray	r;

	init_colors(colors);
	r.o = v_env->cam.o;
	y = -1;
	while (++y < v_env->aa)
	{
		x = -1;
		while (++x < v_env->aa)
		{
			r.n = compute_aa_ray(v_env->aa, x, y, rt_s);
			ray_trace(&r, dst_color, v_env);
			colors[0] += dst_color->r;
			colors[1] += dst_color->g;
			colors[2] += dst_color->b;
		}
	}
	aa2 = v_env->aa * v_env->aa;
	*dst_color = (t_color){colors[0] / aa2, colors[1] / aa2, colors[2] / aa2};
}
