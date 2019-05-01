/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tanglecube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:41:19 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/01 16:13:01 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_tanglecube_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.x = 4 * pow(intersect.x, 3) - 10.0 * intersect.x;
	intersect.y = 4 * pow(intersect.y, 3) - 10.0 * intersect.y;
	intersect.z = 4 * pow(intersect.z, 3) - 10.0 * intersect.z;
	return (vec3d_unit(intersect));
}

double	get_tanglecube_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quartic	quartic;

	quartic.a = pow(direction.x, 4) + pow(direction.y, 4) + pow(direction.z, 4);
	quartic.b = 4.0 * (pow(direction.x, 3) * origin.x
			+ pow(direction.y, 3) * origin.y
			+ pow(direction.z, 3) * origin.z);
	quartic.c = 6.0 * (pow(direction.x, 2) * pow(origin.x, 2)
			+ pow(direction.y, 2) * pow(origin.y, 2)
			+ pow(direction.z, 2) * pow(origin.z, 2))
		- 5.0 * (pow(direction.x, 2) + pow(direction.y, 2)
			+ pow(direction.z, 2));
	quartic.d = 4.0 * (pow(origin.x, 3) * direction.x
			+ pow(origin.y, 3) * direction.y + pow(origin.z, 3) * direction.z)
		- 10.0 * vec3d_dot(origin, direction);
	quartic.e = pow(origin.x, 4) + pow(origin.y, 4) + pow(origin.z, 4)
		- 5.0 * vec3d_length2(origin) + object->radius;
	return (solve_quartic_equation(&quartic));
}
