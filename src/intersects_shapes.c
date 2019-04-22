/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects_shapes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:46:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 21:49:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "solver.h"
#include "vec3d.h"

double	get_plane_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	double	distance;

	(void)object;
	if (fabs(direction.y) > 1e-6)
	{
		distance = origin.y / -direction.y;
		if (distance >= .0)
			return (distance);
	}
	return (-1);
}

double	get_cone_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;
	double	cos_r2;

	cos_r2 = pow(cos(object->radius), 2);
	quad.a = pow(direction.z, 2) - cos_r2;
	quad.b = 2 * (direction.z * origin.z - vec3d_dot(direction, origin)
			* cos_r2);
	quad.c = pow(origin.z, 2) - vec3d_length2(origin) * cos_r2;
	return (solve_quadratic_equation(&quad));
}

double	get_torus_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quartic	quartic;
	double		tmp[3];

	quartic.tmp1 = vec3d_length2(direction);
	quartic.tmp2 = vec3d_dot(direction, origin);
	quartic.tmp3 = vec3d_length2(origin);
	tmp[0] = pow(object->big_radius, 2);
	tmp[1] = pow(object->radius, 2);
	tmp[2] = tmp[0] + tmp[1];
	quartic.a = pow(quartic.tmp1, 2);
	quartic.b = 4 * quartic.tmp1 * quartic.tmp2;
	quartic.c = 2 * quartic.tmp1 * (quartic.tmp3 - tmp[2]) + 4
		* pow(quartic.tmp2, 2) + 4 * tmp[0] * pow(direction.y, 2);
	quartic.d = 4 * (quartic.tmp3 - tmp[2]) * quartic.tmp2 + 8 * tmp[0]
		* (origin.y * direction.y);
	quartic.e = pow(quartic.tmp3 - tmp[2], 2) - 4 * tmp[0]
		* (tmp[1] - pow(origin.y, 2));
	return (solve_quartic_equation(&quartic));
}

double	get_sphere_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;

	quad.a = vec3d_length2(direction);
	quad.b = 2 * vec3d_dot(origin, direction);
	quad.c = vec3d_length2(origin) - pow(object->radius, 2);
	return (solve_quadratic_equation(&quad));
}

double	get_cylinder_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;

	quad.a = pow(direction.x, 2) + pow(direction.y, 2);
	quad.b = 2 * (direction.x * origin.x + direction.y * origin.y);
	quad.c = pow(origin.x, 2) + pow(origin.y, 2) - pow(object->radius, 2);
	return (solve_quadratic_equation(&quad));
}
