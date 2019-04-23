/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:36:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/24 00:08:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_object.h"

static void	assign_object_functions2(t_ray_object *object)
{
	if (object->type == RAYOBJ_CONE)
	{
		object->intersect = get_cone_intersect_dist;
		object->normal = get_cone_cylinder_normal;
	}
	else if (object->type == RAYOBJ_TORUS)
	{
		object->intersect = get_torus_intersect_dist;
		object->normal = get_torus_normal;
	}
	else if (object->type == RAYOBJ_TRIANGLE)
	{
		object->intersect = get_triangle_intersect_dist;
		object->normal = get_triangle_normal;
	}
	else if (object->type == RAYOBJ_ELLIPSOID)
	{
		object->intersect = get_ellipsoid_intersect_dist;
		object->normal = get_ellipsoid_normal;
	}
	else if (object->type == RAYOBJ_HYPERBOLOID)
	{
		object->intersect = get_hyperboloid_intersect_dist;
		object->normal = get_hyperboloid_nornal;
	}
}

void		assign_object_functions(t_ray_object *object)
{
	if (object->type == RAYOBJ_SPHERE)
	{
		object->intersect = get_sphere_intersect_dist;
		object->normal = get_intersect_as_normal;
	}
	else if (object->type == RAYOBJ_PLANE)
	{
		object->intersect = get_plane_intersect_dist;
		object->normal = get_plane_normal;
	}
	else if (object->type == RAYOBJ_CYLINDER)
	{
		object->intersect = get_cylinder_intersect_dist;
		object->normal = get_cone_cylinder_normal;
	}
	else
		assign_object_functions2(object);
}
