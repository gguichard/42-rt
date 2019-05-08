/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 23:44:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "quaternion.h"
#include "vec3d.h"
#include "effects.h"

void			intersect_primary_ray(t_data *data, t_ray_inf *ray_inf)
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
				&& (ray_inf->object == NULL || hit.dist < ray_inf->dist))
			{
				ray_inf->object = obj;
				ray_inf->dist = hit.dist;
				ray_inf->normal = quat_rot_with_quat(hit.normal
						, obj->inv_rot_quat);
			}
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
	return (color);
}

static t_vec3d	get_sky_color(t_vec3d ray_dir)
{
	double	factor;
	t_vec3d	color;
	t_vec3d	sky_color;

	factor = 0.5 * (ray_dir.y + 1.0);
	color = vec3d_scalar(vec3d(1, 1, 1), 1.0 - factor);
	sky_color = vec3d_scalar(vec3d(0.5, 0.7, 1.0), factor);
	return (vec3d_add(color, sky_color));
}

t_vec3d			trace_primary_ray(t_data *data, t_vec3d origin, t_vec3d ray_dir
	, int depth)
{
	t_ray_inf	ray_inf;
	t_vec3d		color;

	color = vec3d(0, 0, 0);
	if (depth > 0)
	{
		ray_inf.origin = origin;
		ray_inf.direction = ray_dir;
		ray_inf.object = NULL;
		ray_inf.dist = INFINITY;
		intersect_primary_ray(data, &ray_inf);
		if (ray_inf.object == NULL)
			color = get_sky_color(ray_dir);
		else
		{
			ray_inf.normal = vec3d_unit(ray_inf.normal);
			ray_inf.intersect = vec3d_add(ray_inf.origin
					, vec3d_scalar(ray_inf.direction, ray_inf.dist));
			color = trace_light_and_recursive_rays(data, &ray_inf, depth);
		}
		color = apply_effects(data, &ray_inf, color
				, (ray_inf.object == NULL ? color : ray_inf.object->color));
	}
	return (color);
}
