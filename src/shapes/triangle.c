/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:30:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 03:24:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"

static t_vec3d	get_triangle_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	tmp1;
	t_vec3d	tmp2;

	(void)hit;
	tmp1 = vec3d_sub(object->vertices[1], object->vertices[0]);
	tmp2 = vec3d_sub(object->vertices[2], object->vertices[0]);
	return (vec3d_unit(vec3d_cross(tmp1, tmp2)));
}

void			hit_triangle(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	tmp[5];
	double	var[4];

	tmp[0] = vec3d_sub(object->vertices[1], object->vertices[0]);
	tmp[1] = vec3d_sub(object->vertices[2], object->vertices[0]);
	tmp[2] = vec3d_cross(hit->direction, tmp[1]);
	var[0] = vec3d_dot(tmp[0], tmp[2]);
	if (fabs(var[0]) < EPSILON)
		return ;
	var[1] = 1.0 / var[0];
	tmp[3] = vec3d_sub(hit->origin, object->vertices[0]);
	var[2] = var[1] * vec3d_dot(tmp[3], tmp[2]);
	if (var[2] < 0.0 || var[2] > 1.0)
		return ;
	tmp[4] = vec3d_cross(tmp[3], tmp[0]);
	var[3] = var[1] * vec3d_dot(hit->direction, tmp[4]);
	if (var[3] < 0.0 || var[2] + var[3] > 1.0)
		return ;
	var[0] = var[1] * vec3d_dot(tmp[1], tmp[4]);
	if (var[0] > EPSILON)
	{
		hit->dist = var[0];
		hit->normal = get_triangle_normal(object, hit);
	}
}
