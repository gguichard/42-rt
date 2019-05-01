/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:52 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/01 04:34:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "raytracer.h"
#include "ray_inf.h"
#include "ray_object.h"
#include "quaternion.h"
#include "vec3d.h"

t_vec3d	get_ray_dir(t_data *data, int x, int y)
{
	double	pixel_x;
	double	pixel_y;
	t_vec3d	dir;

	pixel_x = (2 * (x + .5) / data->winsize.width - 1) * data->camera.fov
		* data->winsize.aspect_ratio;
	pixel_y = (1 - (2 * (y + .5) / data->winsize.height)) * data->camera.fov;
	dir = vec3d_scalar(data->camera.right, pixel_x);
	dir = vec3d_add(dir, vec3d_scalar(data->camera.up, pixel_y));
	dir = vec3d_add(dir, data->camera.direction);
	return (vec3d_unit(dir));
}

void	world_to_object_transform(t_ray_inf *ray_inf, t_ray_object *object
		, t_vec3d *origin, t_vec3d *direction)
{
	*origin = vec3d_sub(ray_inf->origin, object->origin);
	*origin = quat_rot_with_quat(*origin, object->quat_rotate);
	*direction = quat_rot_with_quat(ray_inf->direction, object->quat_rotate);
	*direction = vec3d_unit(*direction);
}

int		has_object_in_ray(t_data *data, t_ray_inf *ray_inf
		, double max_dist_squared)
{
	size_t			index;
	t_ray_object	*obj;
	t_vec3d			origin;
	t_vec3d			direction;
	double			dist;

	index = 0;
	while (index < data->objects.size)
	{
		obj = (t_ray_object *)data->objects.data[index];
		world_to_object_transform(ray_inf, obj, &origin, &direction);
		dist = obj->intersect(obj, origin, direction);
		if (dist > NEAR_PLANE_CLIPPING && (dist * dist) < max_dist_squared)
			return (1);
		index++;
	}
	return (0);
}
