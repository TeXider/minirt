/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 20:15:50 by almighty          #+#    #+#             */
/*   Updated: 2026/06/11 20:27:10 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

void	print_vector(t_vector *v, char *name, bool nl)
{
	printf("vector %s: %f %f %f  ", name, v->x, v->y, v->z);
	if (nl)
		write(1, "\n", 1);
}

void	print_color(t_color *c, char *name, bool nl)
{
	printf("color %s: %d %d %d  ", name, c->r, c->g, c->b);
	if (nl)
		write(1, "\n", 1);
}

void	print_float(float n, char *name, bool nl)
{
	printf("float %s: %f  ", name, n);
	if (nl)
		write(1, "\n", 1);
}

void	print_int(int n, char *name, bool nl)
{
	printf("int %s: %d  ", name, n);
	if (nl)
		write(1, "\n", 1);
}
