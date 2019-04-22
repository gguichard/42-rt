/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:07:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/22 03:11:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "quaternion.h"
#include "vec3d.h"

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

t_vec3d			rotate_by_quaternion(t_vec3d vec, t_vec3d rot_vec, double angle)
{
	t_quaternion	quat_vec_dir;
	t_quaternion	quat_rot_vec;
	t_quaternion	quat_result;

	quat_rot_vec = vec3d_to_rotate_quaternion(rot_vec, angle);
	quat_vec_dir.x = vec.x;
	quat_vec_dir.y = vec.y;
	quat_vec_dir.z = vec.z;
	quat_vec_dir.scalar = 0;
	quat_result = quaternion_mul(quat_rot_vec, quat_vec_dir);
	quat_result = quaternion_mul(quat_result, quaternion_conj(quat_rot_vec));
	vec.x = quat_result.x;
	vec.y = quat_result.y;
	vec.z = quat_result.z;
	return (vec);
}
