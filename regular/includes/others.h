/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:47:13 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/02 18:43:29 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHERS_H
# define OTHERS_H

# include "vector.h"
# include <stdlib.h>

# define INVALID_ARG_COUNT_MSG	"./minirt : Invalid argument count"
# define INVALID_ARG_COUNT_HINT	"Usage: ./minirt [rt_scene_path]"
# define MLX_INIT_ERR_MSG		"MinilibX failed to initiate"
# define MLX_INIT_ERR_HINT		"Oh... well... there's nothing we can do"
# define INVALID_FILE_EXTENSION	""
# define MALLOC_ERR				"Fatal malloc() error:"
# define MALLOC_ERR_HINT		"Time to go touch some grass my friend"
# define FILE_ERR				""
# define READ_ERR				"Fatal read() error:"
# define READ_ERR_HINT			"Why do you look at me like its my fault?"
# define PARSING	0
# define INIT		1
# define SYSTEM		2

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

typedef struct s_parsing
{
	int		fd;
	char	buff[1028];
	int		i;
	int		read_len;
	bool	is_parsing_over;
	int		line_count;
}	t_parsing;


bool	safe_alloc(void **dst, size_t size);
bool	safe_realloc(void **dst, size_t oldsize, size_t newsize);

#endif