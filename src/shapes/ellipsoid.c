/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:32:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/07 17:59:03 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_ellipsoid_normal(t_ray_object *object, t_ray_hit *hit
	, double dist)
{
	t_vec3d	normal;

	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, dist));
	normal.x /= (object->size.x * object->size.x);
	normal.y /= (object->size.y * object->size.y);
	normal.z /= (object->size.z * object->size.z);
	return (vec3d_unit(normal));
}

void			hit_ellipsoid(t_ray_object *object, t_ray_hit *hit)
{
	double	tmp[3];

	tmp[0] = object->size.x * object->size.x;
	tmp[1] = object->size.y * object->size.y;
	tmp[2] = object->size.z * object->size.z;
	hit->quad.a = hit->direction.x * hit->direction.x / tmp[0]
		+ hit->direction.y * hit->direction.y / tmp[1]
		+ hit->direction.z * hit->direction.z / tmp[2];
	hit->quad.b = (2 * hit->origin.x * hit->direction.x) / tmp[0]
		+ (2 * hit->origin.y * hit->direction.y) / tmp[1]
		+ (2 * hit->origin.z * hit->direction.z) / tmp[2];
	hit->quad.c = hit->origin.x * hit->origin.x / tmp[0] + hit->origin.y
		* hit->origin.y / tmp[1] + hit->origin.z * hit->origin.z / tmp[2] - 1;
	solve_quadratic_equation(&hit->quad);
	hit->dist = add_limit_to_object(object, hit->quad.t2, hit);
	hit->normal = get_ellipsoid_normal(object, hit, hit->dist);
	hit->dist_b = add_limit_to_object(object, hit->quad.t1, hit);
	hit->normal_b = vec3d_scalar(get_ellipsoid_normal(
				object, hit, hit->dist_b), -1);
	if (hit->dist < 0)
	{
		hit->dist = hit->dist_b;
		hit->normal = hit->normal_b;
	}
}
