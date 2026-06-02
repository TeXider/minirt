/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 21:51:19 by almighty          #+#    #+#             */
/*   Updated: 2026/06/02 11:36:25 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include "../includes/shapes.h"
#define PI 3.14159265358979323846

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_wadahelli
{
	void	*mlx;
	t_data	*img;
	void	*mlx_win;
	long	last_img_timestamp;
	float	y;
}	t_wadahelli;

void	mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float	get_intensity(t_ray *ray, float res, t_sphere *sphere)
{
	t_vector	point = point_on_ray(ray, res);
	t_vector	radius = vector_sub(&point, &sphere->o);
	t_vector	light = {0, 3 ,0};

	t_vector	aaaah = vector_sub(&light, &point);
	vector_normalize(&aaaah);
	float	intensity = vector_dot_prod(&aaaah, &radius);
	if (intensity <= 0.0)
		return (0.0);
	return (intensity);
}

void	sphere_test(t_data *img, float y)
{
	t_ray	ray;
	t_sphere	sphere;
	float		res;

	sphere.o.x = 2;
	sphere.o.y = y;
	sphere.o.z = 0;
	sphere.r = 1;
	init_vector(&ray.o, 0, 0, 0);
	float	ray_z_to_xy;
	for (float i = 0; i < 600; i++)
	{
		ray.n.z = sin(PI / 4.0 - (PI * i / 1200.0));
		ray_z_to_xy = cos(PI / 4.0 - (PI * i / 1200.0));
		for (float j = 0; j < 600; j++)
		{
			ray.n.x = cos(PI / 4.0 - (PI * j / 1200.0)) * ray_z_to_xy;
			ray.n.y = -sin(PI / 4.0 -  (PI * j / 1200.0)) * ray_z_to_xy;
			if (get_sphere_intersection(&sphere, &ray, &res))
			{
				mlx_put_pixel(img, j, i, (int)(0xFF * get_intensity(&ray, res, &sphere)) << 16);
			}
		}
	}
}
#include <sys/time.h>
int	niggas(void *uh)
{
	struct timeval t;
	t_wadahelli *saywallahi = uh;

	gettimeofday(&t, NULL);
	if (t.tv_usec + t.tv_sec * 1000000L - saywallahi->last_img_timestamp >= 10000)
	{
	sphere_test(saywallahi->img, saywallahi->y);
	saywallahi->y += 0.01;
	saywallahi->last_img_timestamp = t.tv_usec + t.tv_sec * 1000000L;
	mlx_put_image_to_window(saywallahi->mlx, saywallahi->mlx_win, saywallahi->img->img, 0, 0);
	}
	return (0);
}
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 600, "Hello world!");
	img.img = mlx_new_image(mlx, 600, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	t_wadahelli	ninja;
	ninja.img = &img;
	ninja.mlx = mlx;
	ninja.mlx_win = mlx_win;
	struct timeval t;
	gettimeofday(&t, NULL);
	ninja.last_img_timestamp = t.tv_usec + t.tv_sec * 1000000L;
	ninja.y = -0.5;
	mlx_loop_hook(mlx, niggas, &ninja);
	mlx_loop(mlx);
}