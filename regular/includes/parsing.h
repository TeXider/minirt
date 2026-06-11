/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:08:18 by almighty          #+#    #+#             */
/*   Updated: 2026/06/11 12:57:50 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "env.h"

# define NO_PARSING_ERR			0
# define UNKNOWN_ELEMENT_ERR	-1
# define INVALID_FIELD_ERR		-2
# define MISSING_FIELD_ERR		-3
# define EXTRA_FIELD_ERR		-4
# define MULTI_DEF_ERR			-5
# define OUT_OF_RANGE_ERR		-6

# define ALIGHT		0b0001
# define CAM		0b0010
# define LIGHT		0b0011
# define PLANE		0b0100
# define SPHERE		0b1000
# define CYLINDER	0b1100

# define SINGLETON_MASK	0b0011
# define SHAPE_MASK		0b1100

# define BUFF_SIZE	128

typedef struct s_env	t_env;
typedef struct s_visual_env	t_visual_env;

typedef struct s_file
{
	int		fd;
	char	buff[BUFF_SIZE];
	size_t	buff_i;
	long	read_len;
	bool	eof;
}	t_file;

typedef struct s_parsing
{
	t_file	file;
	char	*line;
	size_t	line_i;
	size_t	line_count;
	bool	comma_expected;
	int		parsing_id;
	bool	eop;
	char	*curr_field_name;
	size_t	curr_field_i;
	int		parsing_err;
	t_env	*env;
}	t_parsing;

bool	parse_file(t_env *env);

bool	go_to_next_line(t_file *f, t_parsing *p);
bool	is_end_of_field(t_parsing *p);
bool	go_to_next_obj(t_parsing *p);
bool	go_to_next_field(char *field_name, t_parsing *p);
bool	check_end_of_obj(t_parsing *p);

bool	parse_alight(t_parsing *p, t_visual_env *v_env);
bool	parse_cam(t_parsing *p, t_visual_env *v_env);
bool	parse_light(t_parsing *p, t_visual_env *v_env);
bool	parse_plane(t_parsing *p, t_visual_env *v_env);
bool	parse_sphere(t_parsing *p, t_visual_env *v_env);
bool	parse_cylinder(t_parsing *p, t_visual_env *v_env);

#endif