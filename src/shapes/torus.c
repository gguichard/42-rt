/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:30:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/28 16:30:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_torus_normal(t_ray_object *object, t_vec3d intersect)
{
	double	big_radius2;
	double	tmp;

	big_radius2 = object->big_radius * object->big_radius;
	tmp = vec3d_length2(intersect)
		- (object->radius * object->radius + big_radius2);
	intersect.x *= tmp;
	intersect.y *= tmp + 2 * big_radius2;
	intersect.z *= tmp;
	return (vec3d_unit(intersect));
}

double	get_torus_dist(t_ray_object *object, t_vec3d origin, t_vec3d direction)
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
