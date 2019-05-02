/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:36:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 23:16:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_object.h"

void	assign_object_functions(t_ray_object *object)
{
	if (object->type == RAYOBJ_CONE)
		object->intersect = get_cone_dist;
	else if (object->type == RAYOBJ_TORUS)
		object->intersect = get_torus_dist;
	else if (object->type == RAYOBJ_TRIANGLE)
		object->intersect = get_triangle_dist;
	else if (object->type == RAYOBJ_ELLIPSOID)
		object->intersect = get_ellipsoid_dist;
	else if (object->type == RAYOBJ_HYPERBOLOID)
		object->intersect = get_hyperboloid_dist;
	else if (object->type == RAYOBJ_SPHERE)
		object->intersect = get_sphere_dist;
	else if (object->type == RAYOBJ_PLANE)
		object->intersect = get_plane_dist;
	else if (object->type == RAYOBJ_CYLINDER)
		object->intersect = get_cylinder_dist;
	else if (object->type == RAYOBJ_TANGLECUBE)
		object->intersect = get_tanglecube_dist;
}
