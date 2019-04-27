/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:47:15 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/27 05:43:32 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perturbations.h"
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
	else if (ray_inf->object->normal_circle != 0.0)
		ray_inf->normal = normal_sin_perturbation(ray_inf->normal);
}

t_vec3d	add_color_perturbation(t_ray_inf *ray_inf, t_vec3d color)
{
	if (ray_inf->object->checkerboard.on)
	{
		return (checkerboard(ray_inf->intersect
				, ray_inf->object->checkerboard.color, color));
	}
	return (color);
}
