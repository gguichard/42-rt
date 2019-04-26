/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/26 04:29:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"

static t_vec3d	get_specular_color(t_ray_object *light, t_ray_object *object
		, double shine_factor)
{
	double	shine_f;

	shine_f = pow(shine_factor, object->shininess);
	shine_f *= (object->shininess + 2) / (2 * M_PI) * object->specular;
	return (vec3d_scalar(light->color, shine_f));
}

static t_vec3d	compute_shading(t_ray_object *light, t_ray_inf *ray_inf
		, t_ray_inf *light_ray, double cosine_angle)
{
	t_vec3d	diffuse;
	t_vec3d	specular;
	t_vec3d	reflection_dir;
	double	shine_factor;

	if (cosine_angle < .0)
		cosine_angle = 0;
	diffuse = vec3d_scalar(vec3d_mul(
				light->color, ray_inf->object->color), cosine_angle);
	specular = (t_vec3d){0, 0, 0};
	if (cosine_angle > .0 && ray_inf->object->specular > .0)
	{
		reflection_dir = vec3d_reflect(light_ray->direction, light_ray->normal);
		shine_factor = vec3d_dot(reflection_dir, ray_inf->direction);
		shine_factor = (shine_factor > 1 ? 1 : shine_factor);
		if (shine_factor > 0)
			specular = get_specular_color(light, ray_inf->object, shine_factor);
	}
	return (vec3d_scalar(vec3d_add(diffuse, specular)
				, light->intensity / (M_PI * light_ray->dist)));
}

static t_vec3d	compute_light_color(t_data *data, t_ray_object *light
		, t_ray_inf *ray_inf, t_ray_inf *light_ray)
{
	t_vec3d	color;
	double	cosine_angle;

	color = (t_vec3d){0, 0, 0};
	if (light->type == RAYOBJ_AMBIENTLIGHT)
	{
		color = vec3d_mul(ray_inf->object->color
				, vec3d_scalar(light->color, light->intensity));
	}
	else if (!has_object_in_ray(data, light_ray, light_ray->dist))
	{
		cosine_angle = vec3d_dot(light_ray->direction, light_ray->normal);
		color = compute_shading(light, ray_inf, light_ray, cosine_angle);
	}
	return (color);
}

t_vec3d			trace_light_rays(t_data *data, t_ray_inf *ray_inf)
{
	t_vec3d			color;
	t_ray_inf		light_ray;
	size_t			index;
	t_ray_object	*light;

	color = (t_vec3d){0, 0, 0};
	light_ray.normal = ray_inf->normal;
	light_ray.origin = vec3d_add(ray_inf->intersect
			, vec3d_scalar(light_ray.normal, SHADOW_BIAS));
	index = 0;
	while (index < data->lights.size)
	{
		light = (t_ray_object *)data->lights.data[index];
		light_ray.direction = vec3d_sub(light->origin, light_ray.origin);
		light_ray.dist = vec3d_length2(light_ray.direction);
		if (light_ray.dist > .0)
		{
			light_ray.direction = vec3d_unit(light_ray.direction);
			color = vec3d_add(color
					, compute_light_color(data, light, ray_inf, &light_ray));
		}
		index++;
	}
	return (color);
}
