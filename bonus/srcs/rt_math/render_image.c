/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:47:34 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 02:08:02 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

static inline void	compute_cam_ray(t_ray *dst, t_rt_screen *rt_s,
	t_camera *cam)
{
	if (!rt_s->pix_x)
	{
		rt_s->y_sweep = vector_add(rt_s->y_sweep, rt_s->dy_sweep);
		rt_s->sweep = vector_add(cam->n,
				vector_add(rt_s->init_x_sweep, rt_s->y_sweep));
	}
	dst->n = vector_normalize(rt_s->sweep);
	rt_s->sweep = vector_add(rt_s->sweep, rt_s->dx_sweep);
}

static inline void	init_sweep_vals(t_rt_screen *rt_s, t_camera *cam)
{
	rt_s->init_x_sweep = vector_scale(cam->e_y, tanf(cam->h_fov / 2.0f));
	rt_s->dx_sweep = vector_scale(cam->e_y, -2.0f * tanf(cam->h_fov / 2.0f)
			/ WIN_X);
	rt_s->y_sweep = vector_scale(cam->e_z, tanf(cam->h_fov / 2.0f)
			* WIN_Y / WIN_X);
	rt_s->dy_sweep = vector_scale(cam->e_z, -2.0f * tanf(cam->h_fov / 2.0f)
			/ WIN_X);
}

void	render_image(t_env *env)
{
	t_rt_screen	rt_screen;
	t_ray		cam_ray;
	t_color		pix_color;

	if (!env->vis_env.has_cam)
		return ;
	compute_basis(env->vis_env.cam.n, &env->vis_env.cam.e_y,
		&env->vis_env.cam.e_z);
	init_sweep_vals(&rt_screen, &env->vis_env.cam);
	cam_ray.o = env->vis_env.cam.o;
	rt_screen.pix_y = 0;
	while (rt_screen.pix_y < WIN_Y)
	{
		rt_screen.pix_x = 0;
		while (rt_screen.pix_x < WIN_X)
		{
			compute_cam_ray(&cam_ray, &rt_screen, &env->vis_env.cam);
			ray_trace(&cam_ray, &pix_color, &env->vis_env);
			put_pixel_to_img(&env->img, rt_screen.pix_x, rt_screen.pix_y,
				&pix_color);
			rt_screen.pix_x++;
		}
		rt_screen.pix_y++;
	}
}
