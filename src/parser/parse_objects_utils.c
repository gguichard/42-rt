/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:36:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 23:28:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ray_object.h"
#include "error.h"

static void	assign_hit_fn(t_ray_object *object)
{
	if (object->type == RAYOBJ_CONE)
		object->hit_fn = hit_cone;
	else if (object->type == RAYOBJ_TORUS)
		object->hit_fn = hit_torus;
	else if (object->type == RAYOBJ_TRIANGLE)
		object->hit_fn = hit_triangle;
	else if (object->type == RAYOBJ_ELLIPSOID)
		object->hit_fn = hit_ellipsoid;
	else if (object->type == RAYOBJ_HYPERBOLOID)
		object->hit_fn = hit_hyperboloid;
	else if (object->type == RAYOBJ_SPHERE)
		object->hit_fn = hit_sphere;
	else if (object->type == RAYOBJ_PLANE)
		object->hit_fn = hit_plane;
	else if (object->type == RAYOBJ_CYLINDER)
		object->hit_fn = hit_cylinder;
	else if (object->type == RAYOBJ_TANGLECUBE)
		object->hit_fn = hit_tanglecube;
	else if (object->type == RAYOBJ_TRIANGLEMESH)
		object->hit_fn = hit_trianglemesh;
}

t_error		process_object_after_parsing(t_ray_object *object)
{
	if (object->type == RAYOBJ_CSGUNION)
		object->csg_tree.type = CSG_UNION;
	else if (object->type == RAYOBJ_CSGSUB)
		object->csg_tree.type = CSG_SUB;
	else if (object->type == RAYOBJ_CSGINTER)
		object->csg_tree.type = CSG_INTER;
	if (object->csg_tree.type != CSG_NOCSG)
	{
		if (object->csg_tree.left == NULL || object->csg_tree.right == NULL)
		{
			del_ray_object_properties(object);
			return (ERR_SCENEBADFORMAT);
		}
	}
	assign_hit_fn(object);
	return (ERR_NOERROR);
}
