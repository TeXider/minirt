/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:47:13 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/09 17:47:57 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHERS_H
# define OTHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define NO_ERR						0
# define INVALID_ARG_COUNT_ERR		1
# define MLX_INIT_ERR				2
# define INVALID_FILE_EXTENSION_ERR	3
# define MALLOC_ERR					4
# define OPEN_ERR					5
# define READ_ERR					6
# define MLX_XPM_ERR				7

typedef struct s_env		t_env;
typedef struct s_visual_env	t_visual_env;
typedef struct s_parsing	t_parsing;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

t_color	scale_color(t_color c, float k);
t_color	light_color(t_color color, t_color light);
t_color	add_colors(t_color a, t_color b);

bool	extend_planes_len(t_env *env);
bool	extend_spheres_len(t_env *env);
bool	extend_cylinders_len(t_env *env);
bool	extend_cones_len(t_env *env);
bool	extend_lights_len(t_env *env);

void	safe_free(void **ptr);
bool	challoc(char **dst, size_t len, t_env *env);

/*GET_NEXT_LINE*/

typedef struct s_buffer
{
	char	*content;
	ssize_t	len;
	ssize_t	index;
}	t_buffer;

/* Error handling */

void	print_error(t_env *env);
void	print_parsing_error(t_parsing *p);
void	print_declaration_hint(char *parsing_id);
char	*opt_hint1(void);
char	*opt_hint2(void);
void	print_opt_hint(char *parsing_id);
void	print_extra_field_error(t_parsing *p);
void	print_out_of_range_error(t_parsing *p);
void	print_invalid_field_error(t_parsing *p);
void	print_unknown_element_error(t_parsing *p);

#endif