/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:03:38 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/06 07:52:12 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "raytracer.h"
#include "vec3d.h"
#include "solver.h"

static double	check_if_coef_is_neg(t_ray_object *object, double result
	, t_vec3d intersect)
{
	if (object->cut_plane.on_xmax && intersect.x > object->cut_plane.max.x)
		return (-1);
	if (object->cut_plane.on_ymax && intersect.y > object->cut_plane.max.y)
		return (-1);
	if (object->cut_plane.on_zmax && intersect.z > object->cut_plane.max.z)
		return (-1);
	if (object->cut_plane.on_xmin && intersect.x < object->cut_plane.min.x)
		return (-1);
	if (object->cut_plane.on_ymin && intersect.y < object->cut_plane.min.y)
		return (-1);
	if (object->cut_plane.on_zmin && intersect.z < object->cut_plane.min.z)
		return (-1);
	return (result);
}

double			add_limit_to_object(t_ray_object *object, double dist
	, t_ray_hit *hit)
{
	t_vec3d	intersect;

	if (dist < 0)
		return (-1);
	intersect = vec3d_add(hit->origin, vec3d_scalar(hit->direction, dist));
	return (check_if_coef_is_neg(object, dist, intersect));
}
