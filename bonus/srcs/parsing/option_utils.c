/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:11:40 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 16:21:02 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	is_end_of_option(t_parsing *p)
{
	return (!p->line[p->line_i] || p->line[p->line_i] == ' '
		|| p->line[p->line_i] == ';');
}

bool	check_option(char *opt_name, t_parsing *p)
{
	size_t	i;

	if (p->line[p->line_i] == ':' || p->line[p->line_i] == ';'
		|| p->line[p->line_i] == ',')
	{
		p->parsing_err = INVALID_OPT_ERR;
		return (false);
	}
	i = 0;
	while (opt_name[i])
	{
		if (p->line[p->line_i] != opt_name[i])
			return (false);
		p->line_i++;
		i++;
	}
	p->line_i += (p->line[p->line_i] == ':');
	if (!p->line[p->line_i] || p->line[p->line_i] == ' '
		|| p->line[p->line_i] == ';')
	{
		p->parsing_err = INVALID_OPT_ERR;
		return (false);
	}
	return (true);
}

bool	parse_txt(t_img *dst, t_parsing *p)
{
	size_t	i;

	i = 0;
	while (i < 256 && !is_end_of_option(p))
	{
		p->opt_filename[i] = p->line[p->line_i];
		p->line_i++;
		i++;
	}
	p->opt_filename[i] = '\0';
	p->line_i += (p->line[p->line_i] == ';');
	return (open_xpm(dst, p->opt_filename, p->env));
}

void	parse_cam_res(t_camera *cam, t_parsing *p)
{
	cam->r_x = 0;
	cam->r_y = 0;
	if (get_int(&cam->r_x, (int [2]){0, 2000}, ',', p)
		|| (!p->parsing_err && get_int(&cam->r_y, (int [2]){0, 2000}, ';', p)))
		p->parsing_err = INVALID_OPT_ERR;
	cam->r_x += 1280 * !(cam->r_x) + (5 - cam->r_x) * (cam->r_x < 5);
	cam->r_y += 720 * !(cam->r_y) + (5 - cam->r_y) * (cam->r_y < 5);
}
