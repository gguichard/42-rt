/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:47:15 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/29 23:17:47 by gguichar         ###   ########.fr       */
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

t_vec3d	add_color_perturbation(t_ray_inf *ray_inf, t_vec3d base_color)
{
	if (ray_inf->object->checkerboard.size != 0)
	{
		return (apply_checkerboard(ray_inf->intersect, base_color
					, ray_inf->object->checkerboard));
	}
	return (base_color);
}
