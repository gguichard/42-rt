/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 09:00:42 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/21 03:22:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3d.h"
#include "solver.h"

double		vec3d_length_squared(t_vec3d vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double		vec3d_length(t_vec3d vec)
{
	return (sqrt(vec3d_length_squared(vec)));
}

t_vec3d		vec3d_unit(t_vec3d vec)
{
	double	length;

	length = vec3d_length(vec);
	return ((t_vec3d){vec.x / length, vec.y / length, vec.z / length});
}

t_vec3d		vec3d_add(t_vec3d vec_a, t_vec3d vec_b)
{
	return ((t_vec3d){vec_a.x + vec_b.x, vec_a.y + vec_b.y
			, vec_a.z + vec_b.z});
}

t_vec3d		vec3d_sub(t_vec3d vec_a, t_vec3d vec_b)
{
	return ((t_vec3d){vec_a.x - vec_b.x, vec_a.y - vec_b.y
			, vec_a.z - vec_b.z});
}

t_vec3d		vec3d_cross_product(t_vec3d vec_a, t_vec3d vec_b)
{
	return ((t_vec3d){vec_a.y * vec_b.z - vec_a.z * vec_b.y
			, vec_a.z * vec_b.x - vec_a.x * vec_b.z
			, vec_a.x * vec_b.y - vec_a.y * vec_b.x});
}

t_vec3d		vec3d_scalar(t_vec3d vec, double scalar)
{
	return ((t_vec3d){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

double		vec3d_dot_product(t_vec3d vec_a, t_vec3d vec_b)
{
	return (vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z);
}
