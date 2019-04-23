/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 22:34:46 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/24 00:07:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "solver.h"
#include "vec3d.h"

double	get_triangle_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_vec3d	tmp[5];
	double	var[4];
	double	epsilon;

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

double	get_ellipsoid_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;
	double	tmp[3];

	tmp[0] = pow(object->size.x, 2);
	tmp[1] = pow(object->size.y, 2);
	tmp[2] = pow(object->size.z, 2);
	quad.a = pow(direction.x, 2) / tmp[0] + pow(direction.y, 2) / tmp[1]
		+ pow(direction.z, 2) / tmp[2];
	quad.b = (2 * origin.x * direction.x) / tmp[0]
		+ (2 * origin.y * direction.y) / tmp[1]
		+ (2 * origin.z * direction.z) / tmp[2];
	quad.c = pow(origin.x, 2) / tmp[0] + pow(origin.y, 2) / tmp[1]
		+ pow(origin.z, 2) / tmp[2] - 1;
	return (solve_quadratic_equation(&quad));
}

double	get_hyperboloid_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;

	quad.a = pow(direction.z, 2) - pow(direction.x, 2) - pow(direction.y, 2);
	quad.b = 2.0 * (origin.z * direction.z - origin.x * direction.x
			- origin.y * direction.y);
	quad.c = pow(origin.z, 2) + object->radius - pow(origin.x, 2)
		- pow(origin.y, 2);
	return (solve_quadratic_equation(&quad));
}
