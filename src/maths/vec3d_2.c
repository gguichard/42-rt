/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:21:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 19:41:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

t_vec3d	vec3d_mul(t_vec3d vec_a, t_vec3d vec_b)
{
	return (vec3d(vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z));
}

t_vec3d	vec3d_cross(t_vec3d vec_a, t_vec3d vec_b)
{
	return (vec3d(vec_a.y * vec_b.z - vec_a.z * vec_b.y
			, vec_a.z * vec_b.x - vec_a.x * vec_b.z
			, vec_a.x * vec_b.y - vec_a.y * vec_b.x));
}

t_vec3d	vec3d_scalar(t_vec3d vec, double scalar)
{
	return (vec3d(vec.x * scalar, vec.y * scalar, vec.z * scalar));
}

double	vec3d_dot(t_vec3d vec_a, t_vec3d vec_b)
{
	return (vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z);
}

t_vec3d	vec3d_reflect(t_vec3d direction, t_vec3d normal)
{
	return (vec3d_sub(direction
			, vec3d_scalar(normal, 2 * vec3d_dot(direction, normal))));
}
