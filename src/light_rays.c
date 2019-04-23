/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:17 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/23 19:20:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"
#include "color.h"

static t_color	compute_shading(t_ray_object *light, t_ray_inf *ray_inf
		, t_ray_inf *light_ray, double cosine_angle)
{
	t_color	diffuse;
	t_color	specular;
	t_vec3d	reflection_dir;
	double	shine_factor;

	if (cosine_angle < .0)
		cosine_angle = 0;
	diffuse = color_scalar(color_mul(
				light->color, ray_inf->object->color), cosine_angle);
	specular = (t_color){.0, .0, .0};
	if (cosine_angle > .0 && ray_inf->object->specular > .0)
	{
		reflection_dir = vec3d_reflect(light_ray->direction, light_ray->normal);
		shine_factor = vec3d_dot(reflection_dir, ray_inf->direction);
		shine_factor = (shine_factor > 1 ? 1 : shine_factor);
		if (shine_factor > 0)
			specular = color_scalar(light->color, pow(
						shine_factor, ray_inf->object->shininess)
					* (ray_inf->object->shininess + 2)
					/ (2 * M_PI) * ray_inf->object->specular);
	}
	return (color_scalar(color_add(diffuse, specular), light->intensity
				/ (M_PI * light_ray->dist)));
}

static void		compute_light_color(t_data *data, t_ray_object *light
		, t_ray_inf *ray_inf, t_ray_inf *light_ray)
{
	double	cosine_angle;

	if (light->type == RAYOBJ_AMBIENTLIGHT)
	{
		ray_inf->color = color_add(ray_inf->color, color_mul(
					ray_inf->object->color, color_scalar(
						light->color, light->intensity)));
	}
	else if (!has_object_in_ray(data, light_ray, light_ray->dist))
	{
		cosine_angle = vec3d_dot(light_ray->direction, light_ray->normal);
		ray_inf->color = color_add(ray_inf->color, compute_shading(
					light, ray_inf, light_ray, cosine_angle));
	}
}

void			trace_light_rays(t_data *data, t_ray_inf *ray_inf)
{
	t_ray_inf		light_ray;
	t_list			*cur;
	t_ray_object	*light;

	light_ray.normal = ray_inf->normal;
	light_ray.origin = vec3d_add(ray_inf->intersect, vec3d_scalar(
				light_ray.normal, SHADOW_BIAS));
	cur = data->lights;
	while (cur != NULL)
	{
		light = (t_ray_object *)cur->content;
		light_ray.direction = vec3d_sub(light->origin, light_ray.origin);
		light_ray.dist = vec3d_length2(light_ray.direction);
		if (light_ray.dist > 0)
		{
			light_ray.direction = vec3d_unit(light_ray.direction);
			compute_light_color(data, light, ray_inf, &light_ray);
		}
		cur = cur->next;
	}
}
