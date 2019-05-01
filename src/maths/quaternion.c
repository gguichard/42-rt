/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:07:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/01 16:03:39 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "quaternion.h"
#include "vec3d.h"

t_quaternion	quaternion_mul(t_quaternion quat_a, t_quaternion quat_b)
{
	t_quaternion	new;

	new.x = quat_a.w * quat_b.x + quat_a.x * quat_b.w
		+ quat_a.y * quat_b.z - quat_a.z * quat_b.y;
	new.y = quat_a.w * quat_b.y - quat_a.x * quat_b.z
		+ quat_a.y * quat_b.w + quat_a.z * quat_b.x;
	new.z = quat_a.w * quat_b.z + quat_a.x * quat_b.y
		- quat_a.y * quat_b.x + quat_a.z * quat_b.w;
	new.w = quat_a.w * quat_b.w - quat_a.x * quat_b.x
		- quat_a.y * quat_b.y - quat_a.z * quat_b.z;
	return (new);
}

t_quaternion	quaternion_conj(t_quaternion quat)
{
	return ((t_quaternion){-quat.x, -quat.y, -quat.z, quat.w});
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
