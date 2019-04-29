/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:43:23 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/29 23:15:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "perturbations.h"
#include "vec3d.h"

t_vec3d		apply_checkerboard(t_vec3d intersect, t_vec3d base_color
		, t_checkerboard checkerboard)
{
	int	x;
	int	y;
	int	z;

	if (intersect.x < 0)
		intersect.x = -intersect.x + checkerboard.size;
	if (intersect.y < 0)
		intersect.y = -intersect.y + checkerboard.size;
	if (intersect.z < 0)
		intersect.z = -intersect.z + checkerboard.size;
	x = intersect.x / checkerboard.size;
	y = intersect.y / checkerboard.size;
	z = intersect.z / checkerboard.size;
	if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
		return (z % 2 == 0 ? base_color : checkerboard.color);
	else
		return (z % 2 == 0 ? checkerboard.color : base_color);
}
