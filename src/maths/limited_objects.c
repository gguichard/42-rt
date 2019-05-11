/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:03:38 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/11 16:47:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "raytracer.h"
#include "vec3d.h"
#include "solver.h"

int				has_object_limit(t_ray_object *object)
{
	return (object->cut_plane.on_xmax
		|| object->cut_plane.on_ymax
		|| object->cut_plane.on_zmax
		|| object->cut_plane.on_xmin
		|| object->cut_plane.on_ymin
		|| object->cut_plane.on_zmin);
}

static double	check_if_coef_is_neg(t_ray_object *object, double result
	, t_vec3d intersect)
{
	if (object->cut_plane.on_xmax && intersect.x > object->cut_plane.max.x)
		return (-INFINITY);
	else if (object->cut_plane.on_ymax && intersect.y > object->cut_plane.max.y)
		return (-INFINITY);
	else if (object->cut_plane.on_zmax && intersect.z > object->cut_plane.max.z)
		return (-INFINITY);
	else if (object->cut_plane.on_xmin && intersect.x < object->cut_plane.min.x)
		return (-INFINITY);
	else if (object->cut_plane.on_ymin && intersect.y < object->cut_plane.min.y)
		return (-INFINITY);
	else if (object->cut_plane.on_zmin && intersect.z < object->cut_plane.min.z)
		return (-INFINITY);
	else
		return (result);
}

double			add_limit_to_object(t_ray_object *object, t_quad quad
	, t_ray_hit *hit)
{
	t_vec3d	inter[2];
	double	tmp[2];

	if (quad.t1 <= hit->min_dist)
		quad.t1 = -INFINITY;
	if (quad.t2 <= hit->min_dist)
		quad.t2 = -INFINITY;
	if (quad.t1 <= hit->min_dist && quad.t2 <= hit->min_dist)
		return (-INFINITY);
	inter[0] = vec3d_add(hit->origin, vec3d_scalar(hit->direction, quad.t1));
	inter[1] = vec3d_add(hit->origin, vec3d_scalar(hit->direction, quad.t2));
	tmp[0] = check_if_coef_is_neg(object, quad.t1, inter[0]);
	tmp[1] = check_if_coef_is_neg(object, quad.t2, inter[1]);
	if (quad.t2 <= hit->min_dist)
		return (tmp[0]);
	else if (quad.t1 <= hit->min_dist)
		return (tmp[1]);
	else if (tmp[0] <= hit->min_dist && tmp[1] <= hit->min_dist)
		return (-INFINITY);
	else if (tmp[1] <= hit->min_dist)
		return (tmp[0]);
	else if (tmp[0] <= hit->min_dist)
		return (tmp[1]);
	else
		return (tmp[0] < tmp[1] ? tmp[0] : tmp[1]);
}
