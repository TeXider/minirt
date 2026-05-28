/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:40:44 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/27 17:41:30 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct s_ray
{
	t_vector	o;
	t_vector	n;
}	t_ray;

t_vector	point_on_ray(t_ray *ray, float t);

#endif