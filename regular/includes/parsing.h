/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:08:18 by almighty          #+#    #+#             */
/*   Updated: 2026/06/04 22:09:56 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "env.h"

typedef struct s_parsing
{
	int		fd;
	char	buff[1028];
	int		i;
	int		read_len;
	bool	is_parsing_over;
	int		line_count;
}	t_parsing;

bool	parse_file(char *filename, t_env *env);

bool	actualize_buffer(t_parsing *p);
bool	go_to_next_obj(t_parsing *p);
bool	go_to_next_field(t_parsing *p);

#endif