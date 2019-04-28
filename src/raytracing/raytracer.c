/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/28 05:50:28 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "quaternion.h"
#include "vec3d.h"
#include "perturbations.h"

static void		intersect_primary_ray(t_data *data, t_ray_inf *ray_inf)
{
	size_t			index;
	t_ray_object	*obj;
	double			dist;
	t_vec3d			origin;
	t_vec3d			direction;

	index = 0;
	while (index < data->objects.size)
	{
		obj = (t_ray_object *)data->objects.data[index];
		world_to_object_transform(ray_inf, obj, &origin, &direction);
		dist = obj->intersect(obj, origin, direction);
		if (dist > NEAR_PLANE_CLIPPING
				&& (ray_inf->object == NULL || dist < ray_inf->dist))
		{
			ray_inf->object = obj;
			ray_inf->dist = dist;
			ray_inf->normal = obj->normal(obj
					, vec3d_add(origin, vec3d_scalar(direction, dist)));
			ray_inf->normal = rotate_by_quaternion_with_quaternion(
					ray_inf->normal, obj->quat_invert_rotate);
		}
		index++;
	}
}

static t_vec3d	trace_light_and_recursive_rays(t_data *data, t_ray_inf *ray_inf
		, int depth)
{
	t_vec3d	color;
	t_vec3d	base_color;
	t_vec3d	new_color;
	double	fog_scalar;

	add_normal_perturbation(ray_inf);
	base_color = add_color_perturbation(ray_inf, ray_inf->object->color);
	color = trace_light_rays(data, ray_inf, base_color);
	if (ray_inf->object->refractive != 0)
	{
		new_color = trace_refract_ray(data, ray_inf, depth);
		color = vec3d_add(vec3d_scalar(color, 1 - ray_inf->object->rf_factor)
				, vec3d_scalar(new_color, ray_inf->object->rf_factor));
	}
	else if (ray_inf->object->reflective != 0)
	{
		new_color = trace_reflect_ray(data, ray_inf, depth);
		color = vec3d_add(vec3d_scalar(color, 1 - ray_inf->object->reflective)
				, vec3d_scalar(new_color, ray_inf->object->reflective));
	}
	if (data->fog != 0)
	{
		fog_scalar = exp(-pow(ray_inf->dist / data->fog, 2));
		color = vec3d_add(vec3d_scalar((t_vec3d){1, 1, 1}, 1 - fog_scalar)
				, vec3d_scalar(color, fog_scalar));
	}
	return (color);
}

t_vec3d			trace_primary_ray(t_data *data, t_vec3d origin, t_vec3d ray_dir
		, int depth)
{
	t_ray_inf	ray_inf;
	t_vec3d		color;

	color = (t_vec3d){0, 0, 0};
	if (depth > 0)
	{
		ray_inf.origin = origin;
		ray_inf.direction = ray_dir;
		ray_inf.object = NULL;
		intersect_primary_ray(data, &ray_inf);
		if (ray_inf.object != NULL)
		{
			ray_inf.normal = vec3d_unit(ray_inf.normal);
			ray_inf.intersect = vec3d_add(ray_inf.origin
					, vec3d_scalar(ray_inf.direction, ray_inf.dist));
			color = trace_light_and_recursive_rays(data, &ray_inf, depth);
		}
	}
	return (color);
}