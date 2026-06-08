/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:00:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/08 14:01:22 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_end(t_buffer **buff, char **line)
{
	if (*buff)
	{
		if ((*buff)->content)
			free((*buff)->content);
		free(*buff);
		*buff = NULL;
	}
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	return (NULL);
}

static char	buff_init(t_buffer **buff, int fd, ssize_t *index, char reset)
{
	if (!*buff)
	{
		*buff = malloc(sizeof(t_buffer));
		if (!*buff)
			return (2);
		(*buff)->content = malloc(sizeof(char) * BUFFER_SIZE);
		if (!(*buff)->content)
			return (2);
		(*buff)->len = read(fd, (*buff)->content, BUFFER_SIZE);
		if ((*buff)->len < 1)
			return (2);
		*index = 0;
		(*buff)->index = 0;
	}
	else if ((*buff)->index >= (*buff)->len || reset)
	{
		(*buff)->len = read(fd, (*buff)->content, BUFFER_SIZE);
		if ((*buff)->len < 0)
			return (2);
		*index = -1 * reset;
		(*buff)->index = 0;
	}
	else
		*index = (*buff)->index;
	return (((*buff)->len == 0));
}

static char	create_line(char **line, ssize_t len, ssize_t *line_len,
	t_buffer *buff)
{
	ssize_t	i;
	char	*tmp;

	if (!*line)
	{
		*line = malloc(sizeof(char) * (len + 1));
		if (!*line)
			return (1);
	}
	else
	{
		tmp = malloc(sizeof(char) * (*line_len + len + 1));
		i = -1;
		while (++i < *line_len)
			tmp[i] = (*line)[i];
		free(*line);
		*line = tmp;
	}
	i = -1;
	while (++i < len)
		(*line)[i + *line_len] = buff->content[i + buff->index];
	*line_len += len;
	(*line)[*line_len] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer	*buff = NULL;
	char			*line;
	ssize_t			i;
	ssize_t			line_len;

	if (BUFFER_SIZE < 1 || fd < 0 || buff_init(&buff, fd, &i, 0))
		return (gnl_end(&buff, NULL));
	line = NULL;
	line_len = 0;
	while (buff->len && buff->content[i] && buff->content[i] != '\n')
	{
		if (i + 1 >= buff->len)
			if (create_line(&line, i - buff->index + 1, &line_len, buff)
				|| buff_init(&buff, fd, &i, 1) == 2)
				return (gnl_end(&buff, &line));
		i++;
	}
	if (create_line(&line, i - buff->index
			+ (buff->content[i] == '\n' && buff->len), &line_len, buff))
		return (gnl_end(&buff, &line));
	buff->index = i + 1;
	return (line);
}
