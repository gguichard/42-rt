/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:13:59 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/26 22:37:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"
#include "perturbations.h"
#include <math.h>

t_vec3d		normal_sin_perturbation(t_vec3d normal)
{
	normal.x *= sin(normal.x);
	return (normal);
}

t_vec3d		bump_mapping(t_vec3d normal, t_vec3d intersect, double bump)
{
	double		noise_coef[3];
	double		tmp;

	noise_coef[0] = perlin_noise(vec3d_scalar(intersect, 0.1));
	noise_coef[1] = perlin_noise(vec3d_scalar((t_vec3d){intersect.y, intersect.z
				, intersect.x}, 0.1));
	noise_coef[2] = perlin_noise(vec3d_scalar((t_vec3d){intersect.z, intersect.x
				, intersect.y}, 0.1));
	normal.x = (1.0 - bump) * normal.x + bump * noise_coef[0];
	normal.y = (1.0 - bump) * normal.y + bump * noise_coef[1];
	normal.z = (1.0 - bump) * normal.z + bump * noise_coef[2];
	tmp = vec3d_dot(normal, normal);
	if (tmp == 0.0)
		return (normal);
	tmp = 1 / sqrt(tmp);
	return (vec3d_unit(vec3d_scalar(normal, tmp)));
}
