/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:26:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 00:28:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

void	hit_plane(t_ray_object *object, t_ray_hit *hit)
{
	t_quad	quad;
	double	distance;

	(void)object;
	if (fabs(hit->direction.y) > EPSILON)
	{
		distance = -hit->origin.y / hit->direction.y;
		if (distance >= hit->min_dist)
		{
			quad.t1 = distance;
			quad.t2 = distance;
			hit->dist = add_limit_to_object(object, quad, hit);
			hit->normal = vec3d(0, 1, 0);
			if (hit->direction.y > EPSILON)
				hit->normal = vec3d_scalar(hit->normal, -1);
		}
	}
}
