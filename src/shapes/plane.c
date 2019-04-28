/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:26:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/28 16:27:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"

t_vec3d	get_plane_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	(void)intersect;
	return ((t_vec3d){0, 1, 0});
}

double	get_plane_dist(t_ray_object *object, t_vec3d origin, t_vec3d direction)
{
	double	distance;

	(void)object;
	if (fabs(direction.y) > 1e-6)
	{
		distance = -origin.y / direction.y;
		if (distance >= .0)
			return (distance);
	}
	return (-1);
}
