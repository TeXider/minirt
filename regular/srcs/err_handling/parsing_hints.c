/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:57:23 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/07/01 13:19:24 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static char	*shape_hint(char parsing_id)
{
	if (parsing_id == 'p')
		return ("PLANE declaration is as follows (<field>[range]):\n\n"
			"    • pl <origin>[-∞;∞] <normal_vector>[-1.0;1.0] "
			"<color>[0-255]\n\n"
			"    E.g.: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225");
	if (parsing_id == 's')
		return ("SPHERE declaration is as follows (<field>[range]):\n\n"
			"    • sp <origin>[-∞;∞] <diameter>[0.0;∞] <color>[0-255]\n\n"
			"    E.g.: sp 0.0,0.0,20.6 12.6 10,0,255");
	return ("CYLINDER declaration is as follows (<field>[range]):\n\n"
		"    • cy <origin>[-∞;∞] <normal_vector>[-1.0;1.0] "
		"<diameter>[0.0;∞] <height>[0.0;∞] <color>[0-255]\n\n"
		"    E.g.: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255");
}

void	print_declaration_hint(char parsing_id)
{
	char	*msg;

	if (parsing_id == 'A')
		msg = "ALIGHT declaration is as follows (<field>[range]):\n\n"
			"    • A <intensity>[0.0;1.0] <color>[0-255]\n\n"
			"    E.g.: A 0.2 255,255,255";
	else if (parsing_id == 'C')
		msg = "CAMERA declaration is as follows (<field>[range]):\n\n"
			"    • C <origin>[-∞;∞] <normal_vector>[-1.0;1.0] "
			"<horizontal_fov>[0;180]\n\n    E.g.: C -50.0,0,20 0,0,1 70";
	else if (parsing_id == 'L')
		msg = "LIGHT declaration is as follows (<field>[range]):\n\n"
			"    • L <origin>[-∞;∞] <intensity>[0.0;1.0] <color>[0-255]\n\n"
			"    E.g.: L -40.0,50.0,0.0 0.6 10,0,255";
	else
		msg = shape_hint(parsing_id);
	printf("\e[1mⓘ\e[0m   %s\e[0m\n\n", msg);
}
