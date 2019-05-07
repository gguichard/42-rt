/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:30:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 02:50:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_torus_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	normal;
	double	big_radius2;
	double	tmp;

	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, hit->dist));
	big_radius2 = object->big_radius * object->big_radius;
	tmp = vec3d_length2(normal)
		- (object->radius * object->radius + big_radius2);
	normal.x *= tmp;
	normal.y *= (tmp + 2 * big_radius2);
	normal.z *= tmp;
	return (vec3d_unit(normal));
}

void			hit_torus(t_ray_object *object, t_ray_hit *hit)
{
	t_quartic	quartic;
	double		tmp[3];

	quartic.tmp1 = vec3d_length2(hit->direction);
	quartic.tmp2 = vec3d_dot(hit->direction, hit->origin);
	quartic.tmp3 = vec3d_length2(hit->origin);
	tmp[0] = pow(object->big_radius, 2);
	tmp[1] = pow(object->radius, 2);
	tmp[2] = tmp[0] + tmp[1];
	quartic.a = pow(quartic.tmp1, 2);
	quartic.b = 4 * quartic.tmp1 * quartic.tmp2;
	quartic.c = 2 * quartic.tmp1 * (quartic.tmp3 - tmp[2]) + 4
		* pow(quartic.tmp2, 2) + 4 * tmp[0] * pow(hit->direction.y, 2);
	quartic.d = 4 * (quartic.tmp3 - tmp[2]) * quartic.tmp2 + 8 * tmp[0]
		* (hit->origin.y * hit->direction.y);
	quartic.e = pow(quartic.tmp3 - tmp[2], 2) - 4 * tmp[0]
		* (tmp[1] - pow(hit->origin.y, 2));
	hit->dist = solve_quartic_equation(&quartic);
	hit->normal = get_torus_normal(object, hit);
}
