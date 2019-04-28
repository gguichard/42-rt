/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:27:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/28 16:30:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_sphere_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	return (vec3d_unit(intersect));
}

double	get_sphere_dist(t_ray_object *object, t_vec3d origin, t_vec3d direction)
{
	t_quad	quad;

	quad.a = vec3d_length2(direction);
	quad.b = 2 * vec3d_dot(origin, direction);
	quad.c = vec3d_length2(origin) - pow(object->radius, 2);
	return (solve_quadratic_equation(&quad));
}
