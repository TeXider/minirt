/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:08:18 by almighty          #+#    #+#             */
/*   Updated: 2026/06/07 21:23:50 by almighty         ###   ########.fr       */
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

# define ALIGHT		0
# define CAM		1
# define LIGHT		2
# define PLANE		3
# define SPHERE		4
# define CYLINDER	5

typedef struct s_parsing
{
	int		fd;
	char	buff[1028];
	int		i;
	int		read_len;
	bool	parsing_over;
	bool	comma_expected;
	int		line_count;
	int		parsing_ctxt;
	char	*curr_field_name;
	int		curr_field_i;
	int		parsing_err;
	t_env	*env;
}	t_parsing;

bool	parse_file(t_env *env);

bool	refresh_buffer(t_parsing *p);
bool	go_to_next_obj(t_parsing *p);
bool	go_to_next_field(char *field_name, t_parsing *p);
bool	check_fields_over(t_parsing *p);

#endif