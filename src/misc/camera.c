/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:31:31 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/29 20:59:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "quaternion.h"
#include "vec3d.h"

void	init_camera(t_camera *camera)
{
	camera->fov = tan(90 * .5 / 180 * M_PI);
	if (camera->direction.x == 0 && camera->direction.z == 0)
		camera->right = (t_vec3d){0, 0, 1};
	else
	{
		camera->right = rotate_by_quaternion(camera->direction
				, (t_vec3d){0, 1, 0}, M_PI / 2);
	}
	camera->up = rotate_by_quaternion(camera->right
			, camera->direction, M_PI / 2);
}

void	rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle)
{
	t_vec3d	dir;
	t_vec3d	right;
	t_vec3d	up;

	dir = rotate_by_quaternion(camera->direction, rot_vec, angle);
	right = rotate_by_quaternion(camera->right, rot_vec, angle);
	up = vec3d_unit(rotate_by_quaternion(camera->up, rot_vec, angle));
	camera->direction = vec3d_unit(dir);
	camera->right = vec3d_unit(right);
	camera->up = vec3d_unit(up);
}
