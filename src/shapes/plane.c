/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:26:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 02:49:59 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"

void	hit_plane(t_ray_object *object, t_ray_hit *hit)
{
	double	distance;

	(void)object;
	if (fabs(hit->direction.y) > 1e-6)
	{
		distance = -hit->origin.y / hit->direction.y;
		if (distance >= .0)
		{
			hit->dist = distance;
			hit->normal = (t_vec3d){0, 1, 0};
		}
	}
}
