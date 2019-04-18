/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 09:50:23 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/18 12:17:40 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "camera.h"
#include "vec3d.h"

t_vec3d		rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle)
{
	t_quaternion	quat_vec_dir;
	t_quaternion	quat_rot_vec;
	t_quaternion	quat_result;

	quat_rot_vec = vec3d_to_rotate_quaternion(rot_vec, angle);
	quat_vec_dir.x = camera->direction.x;
	quat_vec_dir.y = camera->direction.y;
	quat_vec_dir.z = camera->direction.z;
	quat_vec_dir.scalar = 0;
	quat_result = quaternion_mul(quat_rot_vec, quat_vec_dir);
	quat_result = quaternion_mul(quat_result, quaternion_conj(quat_rot_vec));
	return ((t_vec3d){quat_result.x, quat_result.y, quat_result.z});
}
