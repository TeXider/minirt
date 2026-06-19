/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:47:34 by almighty          #+#    #+#             */
/*   Updated: 2026/06/19 11:56:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/env.h"

static void	init_sweep_vals(t_rt_screen *rt_s, t_camera *cam)
{
	rt_s->v_sweep_comp[0] = cosf(V_FOV / 2.0f - V_FOV / ((float) WIN_Y));
	rt_s->v_sweep_comp[1] = sinf(V_FOV / 2.0f - V_FOV / ((float) WIN_Y));
	rt_s->dv_sweep_rot[0] = cosf(V_FOV / ((float) WIN_Y));
	rt_s->dv_sweep_rot[1] = sinf(V_FOV / ((float) WIN_Y));
	rt_s->init_h_sweep_comp[0] = cosf(cam->h_fov / 2.0f);
	rt_s->init_h_sweep_comp[1] = sinf(cam->h_fov / 2.0f);
	rt_s->h_sweep_comp[0] = rt_s->init_h_sweep_comp[0];
	rt_s->h_sweep_comp[1] = rt_s->init_h_sweep_comp[1];
	rt_s->dh_sweep_rot[0] = cosf(cam->h_fov / ((float) WIN_X));
	rt_s->dh_sweep_rot[1] = sinf(cam->h_fov / ((float) WIN_X));
}

static void	get_camera_basis(t_camera *cam)
{
	float	cos_theta;

	cos_theta = sqrt(1.0f - cam->n.z * cam->n.z);
	if (!cos_theta)
	{
		cam->e_y = (t_vector){0, 1, 0};
		cam->e_z = (t_vector){-1, 0, 0};
	}
	else
	{
		cam->e_y = (t_vector){-cam->n.y / cos_theta, -cam->n.z / cos_theta, 0};
		cam->e_z = (t_vector){-cam->n.x * cam->n.z / cos_theta,
			-cam->n.y * cam->n.z / cos_theta, cos_theta};
	}
}

static void	normalize_vectors(t_visual_env *v_env)
{
	size_t	i;

	v_env->cam.n = vector_normalize(v_env->cam.n);
	i = -1;
	while (++i < v_env->planes_count)
		v_env->planes[i].n = vector_normalize(v_env->planes[i].n);
	i = -1;
	while (++i < v_env->cylinders_count)
		v_env->cylinders[i].n = vector_normalize(v_env->cylinders[i].n);
}

void	render_image(t_env *env)
{
	t_rt_screen	rt_screen;
	t_ray		cam_ray;
	t_color		pix_color;

	env->vis_env.cam.h_fov *= PI / 180.0f;
	normalize_vectors(&env->vis_env);
	get_camera_basis(&env->vis_env.cam);
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
