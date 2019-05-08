/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:52 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 23:42:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
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

void	world_to_object_transform(t_ray_object *object, t_ray_inf *ray_inf
	, t_ray_hit *hit)
{
	hit->origin = vec3d_sub(ray_inf->origin, object->origin);
	hit->origin = quat_rot_with_quat(hit->origin, object->rot_quat);
	hit->direction = quat_rot_with_quat(ray_inf->direction, object->rot_quat);
	hit->direction = vec3d_unit(hit->direction);
}

int		has_object_in_ray(t_data *data, t_ray_inf *ray_inf
	, double max_dist_squared)
{
	size_t			index;
	t_ray_object	*obj;
	t_ray_hit		hit;

	index = 0;
	while (index < data->objects.size)
	{
		obj = (t_ray_object *)data->objects.data[index];
		if (obj->hit_fn != NULL)
		{
			world_to_object_transform(obj, ray_inf, &hit);
			hit.dist = -INFINITY;
			obj->hit_fn(obj, &hit);
			if (hit.dist > NEAR_PLANE_CLIPPING
				&& (hit.dist * hit.dist) < max_dist_squared)
				return (1);
		}
		index++;
	}
	return (0);
}
