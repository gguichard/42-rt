/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:47:15 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/11 19:14:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"
#include "raytracer.h"
#include "ray_inf.h"
#include "vec3d.h"

void	add_normal_perturbation(t_ray_inf *ray_inf)
{
	if (ray_inf->object->bump != 0.0)
		ray_inf->normal = bump_mapping(ray_inf->normal, ray_inf->intersect
				, ray_inf->object->bump, 0);
	else if (ray_inf->object->roughness != 0.0)
		ray_inf->normal = bump_mapping(ray_inf->normal, ray_inf->intersect
				, ray_inf->object->roughness, 1);
	else if (ray_inf->object->wavy_effect)
		ray_inf->normal = wavy_perturbation(ray_inf->normal
				, ray_inf->intersect);
}

t_vec3d	add_color_perturbation(t_ray_inf *ray_inf, t_vec3d base_color)
{
	t_vec3d	intersect;

	intersect = ray_inf->intersect;
	intersect = vec3d_add(intersect
			, vec3d_scalar(ray_inf->normal, SHADOW_BIAS));
	if (ray_inf->object->checker.size != 0)
	{
		return (apply_checkerboard(intersect, base_color
				, ray_inf->object->checker));
	}
	else if (ray_inf->object->perlin.enabled != 0)
	{
		return (perlin_noise_filter(intersect, vec3d(0, 0, 0)
				, base_color, ray_inf->object->perlin.color));
	}
	else if (ray_inf->object->wood.enabled != 0)
	{
		return (wood_filter(intersect, base_color
				, ray_inf->object->wood.color));
	}
	return (base_color);
}
