/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tanglecube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:41:19 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 23:44:59 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_tanglecube_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.x = 4 * pow(intersect.x, 3) - 10.0 * intersect.x;
	intersect.y = 4 * pow(intersect.y, 3) - 10.0 * intersect.y;
	intersect.z = 4 * pow(intersect.z, 3) - 10.0 * intersect.z;
	return (vec3d_unit(intersect));
}

void			get_tanglecube_dist(t_ray_object *object, t_ray_hit *hit)
{
	t_quartic	quartic;

	quartic.a = pow(hit->direction.x, 4) + pow(hit->direction.y, 4)
		+ pow(hit->direction.z, 4);
	quartic.b = 4.0 * (pow(hit->direction.x, 3) * hit->origin.x
			+ pow(hit->direction.y, 3) * hit->origin.y
			+ pow(hit->direction.z, 3) * hit->origin.z);
	quartic.c = 6.0 * (pow(hit->direction.x, 2) * pow(hit->origin.x, 2)
			+ pow(hit->direction.y, 2) * pow(hit->origin.y, 2)
			+ pow(hit->direction.z, 2) * pow(hit->origin.z, 2))
		- 5.0 * (pow(hit->direction.x, 2) + pow(hit->direction.y, 2)
				+ pow(hit->direction.z, 2));
	quartic.d = 4.0 * (pow(hit->origin.x, 3) * hit->direction.x
			+ pow(hit->origin.y, 3) * hit->direction.y
			+ pow(hit->origin.z, 3) * hit->direction.z)
		- 10.0 * vec3d_dot(hit->origin, hit->direction);
	quartic.e = pow(hit->origin.x, 4) + pow(hit->origin.y, 4)
		+ pow(hit->origin.z, 4) - 5.0 * vec3d_length2(hit->origin)
		+ object->radius;
	hit->dist = solve_quartic_equation(&quartic);
	hit->intersect = vec3d_add(hit->origin
			, vec3d_scalar(hit->direction, hit->dist));
	hit->normal = get_tanglecube_normal(object, hit->intersect);
}
