/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:43:23 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/10 17:10:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "effects.h"
#include "ray_object.h"
#include "vec3d.h"

t_vec3d	apply_checkerboard(t_vec3d intersect, t_vec3d base_color
	, t_obj_checker board)
{
	double	sum;
	double	frac;
	double	dumb;

	if (intersect.x < 0)
		intersect.x = -intersect.x + board.size;
	if (intersect.y < 0)
		intersect.y = -intersect.y + board.size;
	if (intersect.z < 0)
		intersect.z = -intersect.z + board.size;
	sum = floor(intersect.x / board.size)
		+ floor(intersect.y / board.size)
		+ floor(intersect.z / board.size);
	frac = modf(sum * .5, &dumb);
	return (frac < EPSILON ? base_color : board.color);
}
