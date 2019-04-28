/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:07:11 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/28 17:07:51 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"
#include "perturbations.h"
#include <math.h>

t_vec3d		bump_mapping(t_vec3d normal, t_vec3d intersect, double bump
	, int type)
{
	double		noise_coef[3];
	double		tmp;

	noise_coef[0] = perlin_noise(vec3d_scalar(intersect, 0.1), type);
	noise_coef[1] = perlin_noise(vec3d_scalar((t_vec3d){intersect.y, intersect.z
				, intersect.x}, 0.1), type);
	noise_coef[2] = perlin_noise(vec3d_scalar((t_vec3d){intersect.z, intersect.x
				, intersect.y}, 0.1), type);
	normal.x = (1.0 - bump) * normal.x + bump * noise_coef[0];
	normal.y = (1.0 - bump) * normal.y + bump * noise_coef[1];
	normal.z = (1.0 - bump) * normal.z + bump * noise_coef[2];
	tmp = vec3d_length2(normal);
	if (tmp == 0.0)
		return (normal);
	tmp = 1.0 / sqrt(tmp);
	return (vec3d_unit(vec3d_scalar(normal, tmp)));
}