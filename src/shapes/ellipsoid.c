/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:32:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 01:19:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_ellipsoid_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	normal;

	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, hit->dist));
	normal.x /= (object->size.x * object->size.x);
	normal.y /= (object->size.y * object->size.y);
	normal.z /= (object->size.z * object->size.z);
	return (vec3d_unit(normal));
}

void			get_ellipsoid_dist(t_ray_object *object, t_ray_hit *hit)
{
	t_quad	quad;
	double	tmp[3];

	tmp[0] = pow(object->size.x, 2);
	tmp[1] = pow(object->size.y, 2);
	tmp[2] = pow(object->size.z, 2);
	quad.a = pow(hit->direction.x, 2) / tmp[0]
		+ pow(hit->direction.y, 2) / tmp[1]
		+ pow(hit->direction.z, 2) / tmp[2];
	quad.b = (2 * hit->origin.x * hit->direction.x) / tmp[0]
		+ (2 * hit->origin.y * hit->direction.y) / tmp[1]
		+ (2 * hit->origin.z * hit->direction.z) / tmp[2];
	quad.c = pow(hit->origin.x, 2) / tmp[0] + pow(hit->origin.y, 2) / tmp[1]
		+ pow(hit->origin.z, 2) / tmp[2] - 1;
	solve_quadratic_equation(&quad);
	hit->dist = add_limit_to_object(object, quad, hit);
	hit->normal = get_ellipsoid_normal(object, hit);
	hit->inside = hit->dist > 0 && quad.t1 >= 0 && hit->dist != quad.t2;
}
