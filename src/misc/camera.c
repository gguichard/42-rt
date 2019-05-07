/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:31:31 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/06 01:37:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "quaternion.h"
#include "vec3d.h"

void	init_camera(t_camera *camera)
{
	t_quaternion	rot;

	rot = xyz_rot_to_quat(camera->rotation);
	camera->direction = vec3d_unit(quat_rot_with_quat(vec3d(0, 0, 1), rot));
	camera->right = vec3d_unit(quat_rot_with_quat(vec3d(1, 0, 0), rot));
	camera->up = vec3d_unit(quat_rot_with_quat(vec3d(0, 1, 0), rot));
}

void	rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle)
{
	t_vec3d	dir;
	t_vec3d	right;
	t_vec3d	up;

	dir = quat_rot(camera->direction, rot_vec, angle);
	right = quat_rot(camera->right, rot_vec, angle);
	up = vec3d_unit(quat_rot(camera->up, rot_vec, angle));
	camera->direction = vec3d_unit(dir);
	camera->right = vec3d_unit(right);
	camera->up = vec3d_unit(up);
}
