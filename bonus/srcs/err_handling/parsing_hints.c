/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:57:23 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/09 16:20:01 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/others.h"

static char	*shape_hint(char *parsing_id)
{
	if (parsing_id[0] == 'P')
		return ("PLANE declaration is as follows (<field>[range]):\n\n"
			"    • pl <origin>[-∞;∞] <normal_vector>[-1.0;1.0] "
			"<color>[0-255]\n\n"
			"    E.g.: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225");
	if (parsing_id[0] == 'S')
		return ("SPHERE declaration is as follows (<field>[range]):\n\n"
			"    • sp <origin>[-∞;∞] <diameter>[0.0;∞] <color>[0-255]\n\n"
			"    E.g.: sp 0.0,0.0,20.6 12.6 10,0,255");
	if (parsing_id[0] == 'C' && parsing_id[1] == 'Y')
		return ("CYLINDER declaration is as follows (<field>[range]):\n\n"
			"    • cy <origin>[-∞;∞] <normal_vector>[-1.0;1.0] "
			"<diameter>[0.0;∞] <height>[0.0;∞] <color>[0-255]\n\n"
			"    E.g.: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255");
	return ("CONE declaration is as follows (<field>[range]):\n\n"
		"    • co <origin>[-∞;∞] <normal_vector>[-1.0;1.0] "
		"<angle>[0;180] <height>[0.0;∞] <color>[0-255]\n\n"
		"    E.g.: co 0,0,0 0,0,1 60 20.1 10,0,255");
}

void	print_declaration_hint(char *parsing_id)
{
	char	*msg;

	if (parsing_id[0] == 'A')
		msg = "ALIGHT declaration is as follows (<field>[range]):\n\n"
			"    • A <intensity>[0.0;1.0] <color>[0-255]\n\n"
			"    E.g.: A 0.2 255,255,255";
	else if (parsing_id[0] == 'C' && parsing_id[1] == 'Y')
		msg = "CAMERA declaration is as follows (<field>[range]):\n\n"
			"    • C <origin>[-∞;∞] <normal_vector>[-1.0;1.0] "
			"<horizontal_fov>[0;180]\n\n    E.g.: C -50.0,0,20 0,0,1 70";
	else if (parsing_id[0] == 'L')
		msg = "LIGHT declaration is as follows (<field>[range]):\n\n"
			"    • L <origin>[-∞;∞] <intensity>[0.0;1.0] <color>[0-255]\n\n"
			"    E.g.: L -40.0,50.0,0.0 0.6 10,0,255";
	else
		msg = shape_hint(parsing_id);
	printf("\e[1mⓘ\e[0m   %s\e[0m\n\n", msg);
}

char	*shape_opt_hint(char *parsing_id)
{
	if (parsing_id[0] == 'S')
		return ("    E.g.: sp 0.0,0.0,20.6 12.6 10,0,255 "
			"txt:sphere.xpm\n"
			"          sp 0.0,0.0,20.6 12.6 10,0,255 check:3.4;bump:bump.xpm");
	if (parsing_id[0] == 'C' && parsing_id[1] == 'Y')
		return ("    E.g.: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255 "
			"txt:cylinder.xpm\n"
			"          cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255 "
			"check:3.4;bump:bump.xpm");
	return ("    E.g.: co 0,0,0 0,0,1 3 20.1 10,0,255 "
		"txt:cone.xpm\n"
		"          co 0,0,0 0,0,1 3 20.1 10,0,255 check:3.4;bump:bump.xpm");
}

void	print_opt_hint(char *parsing_id)
{
	char	*msg;

	msg = NULL;
	if (parsing_id[0] == 'C' && parsing_id[1] == 'A')
		msg = " are the following:\n\n"
			"    • sky:<sky_box/texture/path.xpm>\n"
			"    • res:<WIN_X>[0;2000],<WIN_Y>[0;2000]\n"
			"    • aa:<anti-aliasing value>[0;5]\n\n"
			"    E.g.: C 0.2 255,255,255 res:600,600;sky:box.xpm\n"
			"          C 0.2 255,255,255 aa:3;res:2000,2000";
	else if (parsing_id[0] == 'P')
		msg = " are the following:\n\n"
			"    • check:<checkerboard square size>[0.0;∞]\n"
			"    • txt:<path/to/texture.xpm>\n"
			"    • bump:<path/to/bump_map.xpm>\n\n"
			"    E.g.: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225 txt:plane.xpm\n"
			"          pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225 check:3.4;bump:"
			"bump.xpm";
	if (msg)
		printf("\e[1mⓘ\e[0m   %s %s%s\e[0m\n\n", opt_hint1(), parsing_id, msg);
	else
		printf("\e[1mⓘ\e[0m   %s %s%s%s\e[0m\n\n", opt_hint1(), parsing_id,
			opt_hint2(), shape_opt_hint(parsing_id));
}
