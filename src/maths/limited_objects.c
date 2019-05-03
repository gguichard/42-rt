/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:03:38 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 06:53:56 by roduquen         ###   ########.fr       */
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

double			add_limit_to_object(t_ray_object *object, t_quad quad
		, t_ray_hit *hit)
{
	double	tmp[2];
	t_vec3d	intersect1;
	t_vec3d	intersect2;

	if (quad.t1 < 0 && quad.t2 < 0)
		return (-1);
	intersect1 = vec3d_add(hit->origin, vec3d_scalar(hit->direction, quad.t1));
	intersect2 = vec3d_add(hit->origin, vec3d_scalar(hit->direction, quad.t2));
	tmp[0] = check_if_coef_is_neg(object, quad.t1, intersect1);
	tmp[1] = check_if_coef_is_neg(object, quad.t2, intersect2);
	if (quad.t1 < 0)
		return (tmp[1]);
	if (quad.t2 < 0)
		return (tmp[0]);
	if (tmp[0] < 0 && tmp[1] < 0)
		return (-1);
	if (tmp[0] < 0)
		return (tmp[1]);
	if (tmp[1] < 0)
		return (tmp[0]);
	if (tmp[1] < tmp[0])
		return (tmp[1]);
	return (tmp[0]);
}
