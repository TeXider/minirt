/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 20:15:50 by almighty          #+#    #+#             */
/*   Updated: 2026/06/30 11:16:16 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

void	print_vector(t_vector *v, char *name, bool nl)
{
	printf("vector %s: %f %f %f  ", name, v->x, v->y, v->z);
	if (nl)
		write(1, "\n", 1);
}

void	print_color(t_color *c, char *name, bool nl)
{
	printf("color %s: %d %d %d  ", name, c->r, c->g, c->b);
	if (nl)
		write(1, "\n", 1);
}

void	print_float(float n, char *name, bool nl)
{
	printf("float %s: %f  ", name, n);
	if (nl)
		write(1, "\n", 1);
}

void	print_int(int n, char *name, bool nl)
{
	printf("int %s: %d  ", name, n);
	if (nl)
		write(1, "\n", 1);
}

// static void	init_sweep_vals(t_rt_screen *rt_s, t_camera *cam)
// {
// 	float	v_fov;

// 	v_fov = cam->h_fov * ((float) WIN_Y) / ((float) WIN_X);
// 	rt_s->v_sweep_comp[0] = cosf(v_fov / 2.0f + v_fov / ((float) WIN_Y));
// 	rt_s->v_sweep_comp[1] = sinf(v_fov / 2.0f + v_fov / ((float) WIN_Y));
// 	rt_s->dv_sweep_rot[0] = cosf(v_fov / ((float) WIN_Y));
// 	rt_s->dv_sweep_rot[1] = -sinf(v_fov / ((float) WIN_Y));
// 	rt_s->init_h_sweep_comp[0] = cosf(cam->h_fov / 2.0f);
// 	rt_s->init_h_sweep_comp[1] = sinf(cam->h_fov / 2.0f);
// 	rt_s->h_sweep_comp[0] = rt_s->init_h_sweep_comp[0];
// 	rt_s->h_sweep_comp[1] = rt_s->init_h_sweep_comp[1];
// 	rt_s->dh_sweep_rot[0] = cosf(cam->h_fov / ((float) WIN_X));
// 	rt_s->dh_sweep_rot[1] = -sinf(cam->h_fov / ((float) WIN_X));
// }

// static inline void	rot_comp(float comp[2], float rot_mat[2])
// {
// 	float	tmp;

// 	tmp = comp[0];
// 	comp[0] = comp[0] * rot_mat[0] - comp[1] * rot_mat[1];
// 	comp[1] = tmp * rot_mat[1] + comp[1] * rot_mat[0];
// }

// void	compute_cam_ray(t_ray *dst, t_rt_screen *rt_s, t_camera *cam)
// {
// 	if (!rt_s->pix_x)
// 	{
// 		rot_comp(rt_s->v_sweep_comp, rt_s->dv_sweep_rot);
// 		rt_s->v_sweep = vector_add(vector_scale(cam->n, rt_s->v_sweep_comp[0]),
// 			vector_scale(cam->e_z, rt_s->v_sweep_comp[1]));
// 		rt_s->h_sweep_comp[0] = rt_s->init_h_sweep_comp[0];
// 		rt_s->h_sweep_comp[1] = rt_s->init_h_sweep_comp[1];
// 	}
// 	dst->n = vector_add(vector_scale(rt_s->v_sweep, rt_s->h_sweep_comp[0]),
// 			vector_scale(cam->e_y, rt_s->h_sweep_comp[1]));
// 	rot_comp(rt_s->h_sweep_comp, rt_s->dh_sweep_rot);
// 	// if (rt_s->pix_y == WIN_Y / 2 && rt_s->pix_x % 120 == 0)
// 	// 	printf("dst:%f,%f,%f\n", dst->n.x, dst->n.y, dst->n.z);
// 	// float	tmp;

// 	// tmp = cos(cam->h_fov * WIN_Y / (2.0 * WIN_X) - cam->h_fov * rt_s->pix_y / ((float)WIN_X));
// 	// if (!rt_s->pix_x)
// 	// {
// 	// 	dst->n.z = sin(cam->h_fov * WIN_Y / (2.0 * WIN_X) - cam->h_fov * rt_s->pix_y / ((float)WIN_X));
// 	// }
// 	// dst->n.x = cos(cam->h_fov / 2.0 - cam->h_fov * rt_s->pix_x / WIN_X) + cos(cam->h_fov * WIN_Y / (2.0 * WIN_X) - cam->h_fov * rt_s->pix_y / ((float)WIN_X)) - 1.0;
// 	// dst->n.z = sin(cam->h_fov / 2.0 - cam->h_fov * rt_s->pix_x / WIN_X) * tmp;
// 	// dst->n.y = sin(cam->h_fov * WIN_Y / (2.0 * WIN_X) - cam->h_fov * rt_s->pix_y / ((float)WIN_X));
// 	// if (rt_s->pix_y == WIN_Y - 1 && rt_s->pix_x == WIN_X - 1)
// 	// {
// 	// 		printf("init_h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	printf("dh_comp : %f,%f\n", rt_s->dh_sweep_rot[0], rt_s->dh_sweep_rot[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);
// 	// 	printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);
// 	// 	printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);
// 	// 	printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);
// 	// 	printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);printf("h_comp : %f,%f\n", rt_s->init_h_sweep_comp[0], rt_s->init_h_sweep_comp[1]);
// 	// 	rot_comp(rt_s->init_h_sweep_comp, rt_s->dh_sweep_rot);
// 	// }
// }
