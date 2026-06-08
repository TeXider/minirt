/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:43:46 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/02/04 10:49:36 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_buffer
{
	char	*content;
	ssize_t	len;
	ssize_t	index;
}	t_buffer;

char	*gnl_end(t_buffer **buff, char **line);
char	buff_init(t_buffer **buff, int fd, ssize_t *index, char reset);
char	create_line(char **line, ssize_t len, ssize_t *line_len,
			t_buffer *buff);
char	*get_next_line(int fd);

#endif
