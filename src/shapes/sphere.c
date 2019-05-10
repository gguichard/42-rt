/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:27:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/09 15:58:48 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_sphere_normal(t_ray_object *object, t_ray_hit *hit
	, double dist)
{
	t_vec3d	normal;

	(void)object;
	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, dist));
	return (vec3d_unit(normal));
}

void			hit_sphere(t_ray_object *object, t_ray_hit *hit)
{
	hit->quad.a = vec3d_length2(hit->direction);
	hit->quad.b = 2 * vec3d_dot(hit->origin, hit->direction);
	hit->quad.c = vec3d_length2(hit->origin) - object->radius * object->radius;
	solve_quadratic_equation(&hit->quad);
	hit->dist = add_limit_to_object(object, hit->quad.t2, hit);
	hit->normal = get_sphere_normal(object, hit, hit->dist);
	hit->dist_b = add_limit_to_object(object, hit->quad.t1, hit);
	hit->normal_b = vec3d_scalar(
			get_sphere_normal(object, hit, hit->dist_b), -1);
	if (hit->dist < 0)
	{
		hit->dist = hit->dist_b;
		hit->normal = hit->normal_b;
	}
}
