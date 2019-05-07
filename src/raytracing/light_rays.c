/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 01:38:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"
#include "math_utils.h"

static t_vec3d	get_specular_color(t_ray_object *light, t_ray_object *object
	, double shine_factor)
{
	double	shine_scalar;

	shine_scalar = pow(shine_factor, object->shininess);
	shine_scalar *= (object->shininess + 2) / (2 * M_PI);
	return (vec3d_scalar(light->color, shine_scalar * object->specular));
}

static t_vec3d	compute_shading(t_ray_inf *light_ray, t_ray_inf *ray_inf
	, t_vec3d base_color)
{
	double	cosine_angle;
	t_vec3d	diffuse;
	t_vec3d	specular;
	t_vec3d	reflection_dir;
	double	shine_factor;

	cosine_angle = vec3d_dot(light_ray->direction, light_ray->normal);
	cosine_angle = clamp(cosine_angle, 0, 1);
	diffuse = vec3d_scalar(vec3d_mul(light_ray->object->color, base_color)
			, cosine_angle * ray_inf->object->diffuse);
	specular = vec3d(0, 0, 0);
	if (cosine_angle > .0 && ray_inf->object->specular > .0)
	{
		reflection_dir = vec3d_reflect(light_ray->direction, light_ray->normal);
		shine_factor = vec3d_dot(reflection_dir, ray_inf->direction);
		shine_factor = clamp(shine_factor, 0, 1);
		if (shine_factor > 0)
			specular = get_specular_color(light_ray->object, ray_inf->object
					, shine_factor);
	}
	return (vec3d_scalar(vec3d_add(diffuse, specular)
			, light_ray->object->intensity / (M_PI * light_ray->dist)));
}

static t_vec3d	compute_light_color(t_data *data, t_ray_inf *light_ray
	, t_ray_inf *ray_inf, t_vec3d base_color)
{
	t_vec3d			color;
	t_ray_object	*light;

	color = vec3d(0, 0, 0);
	light = light_ray->object;
	if (light_ray->object->type == RAYOBJ_AMBIENTLIGHT)
	{
		color = vec3d_mul(base_color
				, vec3d_scalar(light->color, light->intensity));
	}
	else if (!has_object_in_ray(data, light_ray, light_ray->dist))
	{
		color = compute_shading(light_ray, ray_inf, base_color);
	}
	return (color);
}

t_vec3d			trace_light_rays(t_data *data, t_ray_inf *ray_inf
	, t_vec3d base_color)
{
	t_vec3d		color;
	t_vec3d		bias;
	t_ray_inf	light_ray;
	size_t		index;

	color = vec3d(0, 0, 0);
	bias = vec3d_scalar(ray_inf->normal, SHADOW_BIAS);
	light_ray.normal = ray_inf->normal;
	light_ray.origin = vec3d_add(ray_inf->intersect, bias);
	index = 0;
	while (index < data->lights.size)
	{
		light_ray.object = (t_ray_object *)data->lights.data[index];
		light_ray.direction = vec3d_sub(light_ray.object->origin
				, light_ray.origin);
		light_ray.dist = vec3d_length2(light_ray.direction);
		if (light_ray.dist > .0)
		{
			light_ray.direction = vec3d_unit(light_ray.direction);
			color = vec3d_add(color, compute_light_color(data, &light_ray
						, ray_inf, base_color));
		}
		index++;
	}
	return (color);
}
