/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:26:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 21:30:20 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"

t_vec3d	get_plane_normal(t_ray_object *object, t_vec3d intersect, double side)
{
	(void)object;
	(void)intersect;
	side++;
	return ((t_vec3d){0, 1, 0});
}

double	get_plane_dist(t_ray_object *object, t_vec3d origin, t_vec3d direction
	, double *side)
{
	double	distance;

	(void)object;
	(void)side;
	if (object->cut_plane.on_xmax && object->cut_plane.on_ymax)
	{
		object->type = RAYOBJ_TRIANGLE;
		object->vertices[0] = (t_vec3d){object->cut_plane.max.x, 0
			, object->cut_plane.max.y};
		object->vertices[2] = (t_vec3d){0, 0, object->cut_plane.max.y};
		return (get_triangle_dist(object, origin, direction, side));
	}
	if (fabs(direction.y) > 1e-6)
	{
		distance = -origin.y / direction.y;
		if (distance >= .0)
			return (distance);
	}
	return (-1);
}
