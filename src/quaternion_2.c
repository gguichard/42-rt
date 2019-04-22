/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:46:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/22 21:47:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "quaternion.h"
#include "vec3d.h"

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
