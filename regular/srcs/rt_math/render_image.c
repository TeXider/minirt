/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:47:34 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 11:24:09 by almighty         ###   ########.fr       */
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

static inline void	get_camera_basis(t_camera *cam)
{
	float	cos_theta;

	cos_theta = sqrt(1.0f - cam->n.z * cam->n.z);
	if (!cos_theta)
	{
		cam->e_z = (t_vector){0, 1, 0};
		cam->e_y = (t_vector){-1, 0, 0};
	}
	else
	{
		cam->e_z = (t_vector){-cam->n.y / cos_theta, cam->n.x / cos_theta, 0};
		cam->e_y = (t_vector){-cam->n.x * cam->n.z / cos_theta,
			-cam->n.y * cam->n.z / cos_theta, cos_theta};
	}
}

static inline void	normalize_vectors(t_visual_env *v_env)
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

	if (!env->vis_env.has_cam)
		return ;
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
