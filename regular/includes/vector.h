/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:24:03 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/05/27 17:37:19 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

void		init_vector(t_vector *v, float x, float y, float z);
t_vector	vector_scale(t_vector *v, float k);
t_vector	vector_add(t_vector *v, t_vector *u);
t_vector	vector_substract(t_vector *v, t_vector *u);
float		vector_dot_product(t_vector *v, t_vector *u);
float		vector_square(t_vector *v);
float		vector_norm(t_vector *v);

#endif