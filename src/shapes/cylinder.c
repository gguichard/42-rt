/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:28:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 02:49:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_cylinder_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	normal;

	(void)object;
	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, hit->dist));
	normal.z = .0;
	return (vec3d_unit(normal));
}

void			hit_cylinder(t_ray_object *object, t_ray_hit *hit)
{
	t_quad	quad;

	quad.a = pow(hit->direction.x, 2) + pow(hit->direction.y, 2);
	quad.b = 2 * (hit->direction.x * hit->origin.x
			+ hit->direction.y * hit->origin.y);
	quad.c = pow(hit->origin.x, 2) + pow(hit->origin.y, 2)
		- pow(object->radius, 2);
	solve_quadratic_equation(&quad);
	hit->dist = add_limit_to_object(object, quad, hit);
	hit->normal = get_cylinder_normal(object, hit);
	hit->inside = hit->dist > 0 && quad.t1 >= 0 && hit->dist != quad.t2;
}
