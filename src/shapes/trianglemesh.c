/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trianglemesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:01:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 05:48:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"

static double	hit_triangle_for_mesh(t_vec3d origin, t_vec3d direction
		, t_vec3d *vertices)
{
	t_vec3d	tmp[5];
	double	var[4];

	tmp[0] = vec3d_sub(vertices[1], vertices[0]);
	tmp[1] = vec3d_sub(vertices[2], vertices[0]);
	tmp[2] = vec3d_cross(direction, tmp[1]);
	var[0] = vec3d_dot(tmp[0], tmp[2]);
	if (var[0] > -EPSILON && var[0] < EPSILON)
		return (-INFINITY);
	var[1] = 1.0 / var[0];
	tmp[3] = vec3d_sub(origin, vertices[0]);
	var[2] = var[1] * vec3d_dot(tmp[3], tmp[2]);
	if (var[2] < 0.0 || var[2] > 1.0)
		return (-INFINITY);
	tmp[4] = vec3d_cross(tmp[3], tmp[0]);
	var[3] = var[1] * vec3d_dot(direction, tmp[4]);
	if (var[3] < 0.0 || var[2] + var[3] > 1.0)
		return (-INFINITY);
	var[0] = var[1] * vec3d_dot(tmp[1], tmp[4]);
	if (var[0] > EPSILON)
		return (var[0]);
	else
		return (-INFINITY);
}

static void		swap_f(double *ptr1, double *ptr2)
{
	double	tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static int		hit_boundingbox(t_vec3d min, t_vec3d max, t_ray_hit *hit)
{
	double	tmin;
	double	tmax;
	double	tymin;
	double	tymax;
	double	tzmin;
	double	tzmax;

	tmin = (min.x - hit->origin.x) / hit->direction.x;
	tmax = (max.x - hit->origin.x) / hit->direction.x;
	if (tmin > tmax)
		swap_f(&tmin, &tmax);
	tymin = (min.y - hit->origin.y) / hit->direction.y;
	tymax = (max.y - hit->origin.y) / hit->direction.y;
	if (tymin > tymax)
		swap_f(&tymin, &tymax);
	if ((tmin > tymax) || (tymin > tmax))
		return (0);
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (min.z - hit->origin.z) / hit->direction.z;
	tzmax = (max.z - hit->origin.z) / hit->direction.z;
	if (tzmin > tzmax)
		swap_f(&tzmin, &tzmax);
	if ((tmin > tzmax) || (tzmin > tmax))
		return (0);
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return (1);
}

void			hit_trianglemesh(t_ray_object *object, t_ray_hit *hit)
{
	double	min_dist;
	double	dist;
	size_t	idx;

	min_dist = -INFINITY;
	if (hit_boundingbox(object->bbox_min, object->bbox_max, hit))
	{
		idx = 0;
		while (idx < object->triangles.size)
		{
			dist = hit_triangle_for_mesh(hit->origin, hit->direction
					, (t_vec3d *)object->triangles.data[idx]);
			if (dist > EPSILON && (min_dist == -INFINITY || dist < min_dist))
				min_dist = dist;
			idx++;
		}
	}
	hit->dist = min_dist;
	hit->normal = (t_vec3d){0, 1, 0};
	hit->inside = 0;
}
