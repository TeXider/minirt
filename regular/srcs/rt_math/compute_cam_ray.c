/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:39:03 by almighty          #+#    #+#             */
/*   Updated: 2026/06/15 16:05:19 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static inline void	rot_comp(float comp[2], float rot_mat[2])
{
	comp[0] = comp[0] * rot_mat[0] + comp[1] * rot_mat[1];
	comp[1] = comp[0] * -rot_mat[1] + comp[1] * rot_mat[0];
}

void	compute_cam_ray(t_ray *dst, t_rt_screen *rt_s, t_camera *cam)
{
	if (!rt_s->pix_x)
	{
		rt_s->h_sweep_comp[0] = rt_s->init_h_sweep_comp[0];
		rt_s->h_sweep_comp[1] = rt_s->init_h_sweep_comp[1];
		rot_comp(rt_s->v_sweep_comp, rt_s->dv_sweep_rot);
		rt_s->v_sweep = vector_add(vector_scale(cam->n, rt_s->v_sweep_comp[0]),
			vector_scale(cam->n, rt_s->v_sweep_comp[1]));
	}
	dst->n = vector_add(vector_scale(cam->e_y, rt_s->v_sweep_comp[0]),
			vector_scale(rt_s->v_sweep, rt_s->v_sweep_comp[1]));
	rot_comp(rt_s->h_sweep_comp, rt_s->dh_sweep_rot);
}
