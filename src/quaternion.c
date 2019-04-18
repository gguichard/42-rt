/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:07:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/18 13:26:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "quaternion.h"
#include "vec3d.h"
#include <stdio.h>

double			quaternion_length(t_quaternion quat)
{
	return (sqrt(quat.x * quat.x + quat.y * quat.y
				+ quat.z * quat.z + quat.scalar * quat.scalar));
}

t_quaternion	quaternion_unit(t_quaternion quat)
{
	double	length;

	length = quaternion_length(quat);
	return ((t_quaternion){quat.x / length, quat.y / length, quat.z / length
			, quat.scalar / length});
}

t_quaternion	quaternion_mul(t_quaternion quat_a, t_quaternion quat_b)
{
	t_quaternion	new;

	new.x = quat_a.scalar * quat_b.x + quat_a.x * quat_b.scalar
		+ quat_a.y * quat_b.z - quat_a.z * quat_b.y;
	new.y = quat_a.scalar * quat_b.y - quat_a.x * quat_b.z
		+ quat_a.y * quat_b.scalar + quat_a.z * quat_b.x;
	new.z = quat_a.scalar * quat_b.z + quat_a.x * quat_b.y
		- quat_a.y * quat_b.x + quat_a.z * quat_b.scalar;
	new.scalar = quat_a.scalar * quat_b.scalar - quat_a.x * quat_b.x
		- quat_a.y * quat_b.y - quat_a.z * quat_b.z;
	return (new);
}

t_quaternion	quaternion_conj(t_quaternion quat)
{
	return ((t_quaternion){-quat.x, -quat.y, -quat.z, quat.scalar});
}

t_quaternion	vec3d_to_rotate_quaternion(t_vec3d vec, double angle)
{
	double	theta;
	double	sin_theta;

	theta = angle / 2;
	sin_theta = sin(theta);
	return ((t_quaternion){vec.x * sin_theta, vec.y * sin_theta
			, vec.z * sin_theta, cos(theta)});
}
