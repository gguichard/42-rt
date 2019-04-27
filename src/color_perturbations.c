/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_perturbations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:43:23 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/27 04:38:32 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"
#include "perturbations.h"

t_vec3d		checkerboard(t_vec3d intersect, t_vec3d color1, t_vec3d color2)
{
	int		x;
	int		y;
	int		z;

	intersect.x = fabs(intersect.x) / 20.0;
	intersect.y = fabs(intersect.y) / 20.0;
	intersect.z = fabs(intersect.z) / 20.0;
	x = (int)(intersect.x);
	y = (int)(intersect.y);
	z = (int)(intersect.z);
	if (z % 2 == 0)
	{
		if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
			return (color1);
		return (color2);
	}
	if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
		return (color2);
	return (color1);
}
