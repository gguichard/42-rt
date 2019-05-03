/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:27:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 02:50:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_sphere_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	normal;

	(void)object;
	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, hit->dist));
	return (vec3d_unit(normal));
}

void			hit_sphere(t_ray_object *object, t_ray_hit *hit)
{
	t_quad	quad;

	quad.a = vec3d_length2(hit->direction);
	quad.b = 2 * vec3d_dot(hit->origin, hit->direction);
	quad.c = vec3d_length2(hit->origin) - pow(object->radius, 2);
	solve_quadratic_equation(&quad);
	hit->dist = add_limit_to_object(object, quad, hit);
	hit->normal = get_sphere_normal(object, hit);
	hit->inside = hit->dist > 0 && quad.t1 >= 0 && hit->dist != quad.t2;
}
