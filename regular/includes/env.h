/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:09:58 by almighty          #+#    #+#             */
/*   Updated: 2026/06/02 15:10:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include <mlx.h>
# include "visual_env.h"

# define WIN_X	1280
# define WIN_Y	720

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_env
{
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	t_visual_env	vis_env;
	char			*err_msg;
	char			*err_hint;
}	t_env;

#endif