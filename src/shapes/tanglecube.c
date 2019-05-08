/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tanglecube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:41:19 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/07 17:58:37 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_tanglecube_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	normal;

	(void)object;
	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, hit->dist));
	normal.x = 4 * normal.x * normal.x * normal.x - 10.0 * normal.x;
	normal.y = 4 * normal.y * normal.y * normal.y - 10.0 * normal.y;
	normal.z = 4 * normal.z * normal.z * normal.z - 10.0 * normal.z;
	return (vec3d_unit(normal));
}

void			hit_tanglecube(t_ray_object *object, t_ray_hit *hit)
{
	t_quartic	quartic;

	quartic.a = pow(hit->direction.x, 4) + pow(hit->direction.y, 4)
		+ pow(hit->direction.z, 4);
	quartic.b = 4.0 * (pow(hit->direction.x, 3) * hit->origin.x
			+ pow(hit->direction.y, 3) * hit->origin.y
			+ pow(hit->direction.z, 3) * hit->origin.z);
	quartic.c = 6.0 * (hit->direction.x * hit->direction.x
			* hit->origin.x * hit->origin.x + hit->direction.y
			* hit->direction.y * hit->origin.y * hit->origin.y
			+ hit->direction.z * hit->direction.z * hit->origin.z
			* hit->origin.z)
		- 5.0 * (hit->direction.x * hit->direction.x + hit->direction.y
				* hit->direction.y + hit->direction.z * hit->direction.z);
	quartic.d = 4.0 * (pow(hit->origin.x, 3) * hit->direction.x
			+ pow(hit->origin.y, 3) * hit->direction.y
			+ pow(hit->origin.z, 3) * hit->direction.z)
		- 10.0 * vec3d_dot(hit->origin, hit->direction);
	quartic.e = pow(hit->origin.x, 4) + pow(hit->origin.y, 4)
		+ pow(hit->origin.z, 4) - 5.0 * vec3d_length2(hit->origin)
		+ object->radius;
	hit->dist = solve_quartic_equation(&quartic);
	hit->normal = get_tanglecube_normal(object, hit);
}
