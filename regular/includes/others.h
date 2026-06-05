/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:47:13 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/04 22:09:45 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHERS_H
# define OTHERS_H

# include <stdlib.h>
# include "env.h"

# define INVALID_ARG_COUNT_ERR		0 //"./minirt : Invalid argument count"
# define INVALID_ARG_COUNT_HINT		"Usage: ./minirt [rt_scene_path]"
# define MLX_INIT_ERR				1//"MinilibX failed to initiate"
# define MLX_INIT_ERR_HINT			"Oh... well... there's nothing we can do"
# define INVALID_FILE_EXTENSION_ERR	2//"Invalid file extension"
# define MALLOC_ERR					3//"Fatal malloc() error:"
# define MALLOC_ERR_HINT			"Time to go touch some grass my friend"
# define OPEN_ERR					4//"open() function error"
# define READ_ERR					5//"read() function error"
# define READ_ERR_HINT				"Why do you look at me like its my fault?"

# define UNKNOWN_ELEMENT_ERR	0b00000
# define INVALID_FIELD_ERR		0b00001
# define MISSING_FIELD_ERR		0b00010
# define EXTRA_FIELD_ERR		0b00011

# define PARSING_TYPE_MASK		0b11100

# define PARSING_ALIGHT			0b00000
# define PARSING_CAM			0b00100
# define PARSING_LIGHT			0b01000
# define PARSING_PLANE			0b01100
# define PARSING_SPHERE			0b10000
# define PARSING_CYLINDER		0b10100

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_pol_coef
{
	float	a;
	float	b;
	float	c;
}	t_pol_coef;

bool	extend_planes_len(t_visual_env *v_env);
bool	extend_spheres_len(t_visual_env *v_env);
bool	extend_cylinders_len(t_visual_env *v_env);

#endif