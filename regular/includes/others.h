/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:47:13 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/08 18:21:10 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHERS_H
# define OTHERS_H

# include <stdlib.h>
# include <unistd.h>
# include "env.h"

# define NO_ERR						0
# define INVALID_ARG_COUNT_ERR		1 //"./minirt : Invalid number of arguments" "Usage: ./minirt [rt_scene_path] (File must end with .rt)"
# define MLX_INIT_ERR				2 //"MinilibX failed to initiate" "Oh... well... there's nothing we can do"
# define INVALID_FILE_EXTENSION_ERR	3 //"Invalid file extension" "Add ".rt" at to the end of the file name"
# define MALLOC_ERR					4 //"Fatal malloc() function error:" "*chuckles* I'm in danger"
# define OPEN_ERR					5 //"open() function error:" "Why do you look at me like its my fault?"
# define READ_ERR					6 //"read() function error:" "Do you want me to fail that bad?"

# define IS_PARSING_ERR	(1 << 31)

typedef struct s_visual_env	t_visual_env;

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

void	safe_free(void **ptr);
bool	challoc(char **dst, size_t len, t_env *env);

/*GET_NEXT_LINE*/

typedef struct s_buffer
{
	char	*content;
	ssize_t	len;
	ssize_t	index;
}	t_buffer;

char	*get_next_line(int fd);

#endif