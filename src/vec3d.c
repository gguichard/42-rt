/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 09:00:42 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/18 10:59:00 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

double		vec3d_length(t_vec3d vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3d		vec3d_add(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){vec1.x + vec2.x, vec1.y + vec2.y
		, vec1.z + vec2.z});
}

t_vec3d		vec3d_sub(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){vec1.x - vec2.x, vec1.y - vec2.y
		, vec1.z - vec2.z});
}

t_vec3d		vec3d_mult_by_scal(double scal, t_vec3d vec)
{
	return ((t_vec3d){vec.x * scal, vec.y * scal, vec.z * scal});
}

t_vec3d		vec3d_unit(t_vec3d vec)
{
	double		length;

	length = vec3d_length(vec);
	return ((t_vec3d){vec.x / length, vec.y / length, vec.z / length});
}
