/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_norm_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:28:23 by almighty          #+#    #+#             */
/*   Updated: 2026/06/19 11:48:07 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

inline t_vector	sphere_surface_norm_vector(t_sphere *sp, t_vector p)
{
	return (vector_normalize(vector_sub(sp->o, p)));
}
