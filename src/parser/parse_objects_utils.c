/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:36:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 02:51:57 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_object.h"

void	assign_object_functions(t_ray_object *object)
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
}
