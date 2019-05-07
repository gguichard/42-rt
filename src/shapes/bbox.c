/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 02:55:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/05 02:56:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_object.h"
#include "vec3d.h"
#include "math_utils.h"

int	hit_boundingbox(t_vec3d min, t_vec3d max, t_ray_hit *hit)
{
	double	xyz_min[3];
	double	xyz_max[3];

	xyz_min[0] = (min.x - hit->origin.x) / hit->direction.x;
	xyz_max[0] = (max.x - hit->origin.x) / hit->direction.x;
	if (xyz_min[0] > xyz_max[0])
		swap_f(&xyz_min[0], &xyz_max[0]);
	xyz_min[1] = (min.y - hit->origin.y) / hit->direction.y;
	xyz_max[1] = (max.y - hit->origin.y) / hit->direction.y;
	if (xyz_min[1] > xyz_max[1])
		swap_f(&xyz_min[1], &xyz_max[1]);
	if ((xyz_min[0] > xyz_max[1]) || (xyz_min[1] > xyz_max[0]))
		return (0);
	if (xyz_min[1] > xyz_min[0])
		xyz_min[0] = xyz_min[1];
	if (xyz_max[1] < xyz_max[0])
		xyz_max[0] = xyz_max[1];
	xyz_min[2] = (min.z - hit->origin.z) / hit->direction.z;
	xyz_max[2] = (max.z - hit->origin.z) / hit->direction.z;
	if (xyz_min[2] > xyz_max[2])
		swap_f(&xyz_min[2], &xyz_max[2]);
	return (!(xyz_min[0] > xyz_max[2] || xyz_min[2] > xyz_max[0]));
}
