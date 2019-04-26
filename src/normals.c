/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/26 17:10:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_object.h"
#include "vec3d.h"
#include <math.h>

t_vec3d	get_intersect_as_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	return (vec3d_unit(intersect));
}

t_vec3d	get_plane_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	(void)intersect;
	return ((t_vec3d){0, 1, 0});
}

t_vec3d	get_cone_cylinder_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.z = .0;
	return (vec3d_unit(intersect));
}

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
