/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:47:15 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/05 06:20:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"
#include "ray_inf.h"
#include "ray_object.h"
#include "vec3d.h"

void	add_normal_perturbation(t_ray_inf *ray_inf)
{
	if (ray_inf->object->bump != 0.0)
		ray_inf->normal = bump_mapping(ray_inf->normal, ray_inf->intersect
				, ray_inf->object->bump, 0);
	else if (ray_inf->object->roughness != 0.0)
		ray_inf->normal = bump_mapping(ray_inf->normal, ray_inf->intersect
				, ray_inf->object->roughness, 1);
	else if (ray_inf->object->sin_normal != 0.0)
		ray_inf->normal = normal_sin_perturbation(ray_inf->normal);
}

t_vec3d	add_color_perturbation(t_ray_inf *ray_inf, t_vec3d base_color)
{
	if (ray_inf->object->checker.size != 0)
	{
		return (apply_checkerboard(ray_inf->intersect, base_color
				, ray_inf->object->checker));
	}
	else if (ray_inf->object->perlin.enabled != 0)
	{
		return (perlin_noise_filter(ray_inf->intersect, (t_vec3d){0, 0, 0}
				, base_color, ray_inf->object->perlin.color));
	}
	else if (ray_inf->object->wood.enabled != 0)
	{
		return (wood_filter(ray_inf->intersect, (t_vec3d){0, 0, 0}
				, ray_inf->object->wood.color, (t_vec3d){0.737, 0.560, 0.560}));
	}
	return (base_color);
}
