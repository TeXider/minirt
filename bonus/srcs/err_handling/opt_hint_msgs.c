/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_hint_msgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:16:20 by almighty          #+#    #+#             */
/*   Updated: 2026/07/09 14:24:13 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*opt_hint1(void)
{
	return ("Options must be declared at the end of the object like this"
		" [opt1:val;opt2:val...]\n"
		"    Available options for");
}

char	*opt_hint2(void)
{
	return (" are the following:\n\n"
		"    • check:<checkerboard square count>[0;100]\n"
		"    • txt:<path/to/texture.xpm>\n"
		"    • bump:<path/to/bump_map.xpm>\n\n");
}
