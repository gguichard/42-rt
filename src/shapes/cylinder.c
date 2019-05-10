/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:28:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/10 21:20:42 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_cylinder_normal(t_ray_object *object, t_ray_hit *hit
	, double dist)
{
	t_vec3d	normal;

	(void)object;
	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, dist));
	normal.z = .0;
	return (vec3d_unit(normal));
}

void			hit_cylinder(t_ray_object *object, t_ray_hit *hit)
{
	hit->quad.a = hit->direction.x * hit->direction.x
		+ hit->direction.y * hit->direction.y;
	hit->quad.b = 2 * (hit->direction.x * hit->origin.x
			+ hit->direction.y * hit->origin.y);
	hit->quad.c = hit->origin.x * hit->origin.x + hit->origin.y * hit->origin.y
		- object->radius * object->radius;
	solve_quadratic_equation(&hit->quad);
	hit->dist = add_limit_to_object(object, hit->quad.t2, hit);
	hit->normal = get_cylinder_normal(object, hit, hit->dist);
	hit->dist_b = add_limit_to_object(object, hit->quad.t1, hit);
	hit->normal_b = vec3d_scalar(get_cylinder_normal(
				object, hit, hit->dist_b), -1);
	if (hit->dist < 0 || (hit->dist_b > 0 && hit->dist_b < hit->dist))
	{
		hit->dist = hit->dist_b;
		hit->normal = hit->normal_b;
	}
}
