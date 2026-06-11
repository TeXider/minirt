/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:41:36 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/06/08 21:20:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_vector	point_on_ray(t_ray *r, float t)
{
	t_vector	tmp;

	tmp = vector_scale(&r->n, t);
	return (vector_add(&r->o, &tmp));
}
