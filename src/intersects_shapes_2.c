/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects_shapes_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 22:34:46 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/23 01:13:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "solver.h"
#include "vec3d.h"
#include <stdio.h>

double	get_triangle_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_vec3d			tmp[5];
	double			var[4];
	double			epsilon;

	epsilon = 1e-6;
	tmp[0] = vec3d_sub(object->vertices[1], object->vertices[0]);
	tmp[1] = vec3d_sub(object->vertices[2], object->vertices[0]);
	tmp[2] = vec3d_cross(direction, tmp[1]);
	var[0] = vec3d_dot(tmp[0], tmp[2]);
	if (var[0] > -epsilon && var[0] < epsilon)
		return (-1);
	var[1] = 1.0 / var[0];
	tmp[3] = vec3d_sub(origin, object->vertices[0]);
	var[2] = var[1] * vec3d_dot(tmp[3], tmp[2]);
	if (var[2] < 0.0 || var[2] > 1.0)
		return (-1);
	tmp[4] = vec3d_cross(tmp[3], tmp[0]);
	var[3] = var[1] * vec3d_dot(direction, tmp[4]);
	if (var[3] < 0.0 || var[2] + var[3] > 1.0)
		return (-1);
	var[0] = var[1] * vec3d_dot(tmp[1], tmp[4]);
	if (var[0] > epsilon)
		return (var[0]);
	return (-1);
}
