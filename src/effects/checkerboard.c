/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:43:23 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/05 20:22:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"
#include "ray_object.h"
#include "vec3d.h"

t_vec3d	apply_checkerboard(t_vec3d intersect, t_vec3d base_color
	, t_obj_checker board)
{
	int	x;
	int	y;
	int	z;

	if (intersect.x < 0)
		intersect.x = -intersect.x + board.size;
	if (intersect.y < 0)
		intersect.y = -intersect.y + board.size;
	if (intersect.z < 0)
		intersect.z = -intersect.z + board.size;
	x = intersect.x / board.size;
	y = intersect.y / board.size;
	z = intersect.z / board.size;
	if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
		return (z % 2 == 0 ? base_color : board.color);
	else
		return (z % 2 == 0 ? board.color : base_color);
}
