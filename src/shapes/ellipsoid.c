/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:32:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 07:56:35 by roduquen         ###   ########.fr       */
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

	tmp[0] = pow(object->size.x, 2);
	tmp[1] = pow(object->size.y, 2);
	tmp[2] = pow(object->size.z, 2);
	hit->quad.a = pow(hit->direction.x, 2) / tmp[0]
		+ pow(hit->direction.y, 2) / tmp[1]
		+ pow(hit->direction.z, 2) / tmp[2];
	hit->quad.b = (2 * hit->origin.x * hit->direction.x) / tmp[0]
		+ (2 * hit->origin.y * hit->direction.y) / tmp[1]
		+ (2 * hit->origin.z * hit->direction.z) / tmp[2];
	hit->quad.c = pow(hit->origin.x, 2) / tmp[0] + pow(hit->origin.y, 2)
		/ tmp[1] + pow(hit->origin.z, 2) / tmp[2] - 1;
	solve_quadratic_equation(&hit->quad);
	hit->dist = add_limit_to_object(object, hit->quad.t2, hit);
	hit->normal = get_ellipsoid_normal(object, hit, hit->dist);
	hit->dist_b = add_limit_to_object(object, hit->quad.t1, hit);
	hit->normal_b = get_ellipsoid_normal(object, hit, hit->dist_b);
	if (hit->dist < 0)
	{
		hit->dist = hit->dist_b;
		hit->normal = hit->normal_b;
		hit->inside = 1;
	}
}
