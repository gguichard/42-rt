/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:13:59 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/26 11:26:41 by roduquen         ###   ########.fr       */
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

t_vec3d		uniform_bump_mapping(t_vec3d normal, double epsilon)
{
	double	x;
	double	y;
	double	z;

	x = perlin_noise((t_vec3d){normal.x - epsilon, normal.y, normal.z})
		- perlin_noise((t_vec3d){normal.x + epsilon, normal.y, normal.z});
	y = perlin_noise((t_vec3d){normal.x, normal.y - epsilon, normal.z})
		- perlin_noise((t_vec3d){normal.x, normal.y + epsilon, normal.z});
	z = perlin_noise((t_vec3d){normal.x, normal.y, normal.z - epsilon})
		- perlin_noise((t_vec3d){normal.x, normal.y, normal.z + epsilon});
	return ((t_vec3d){normal.x + x, normal.y + y, normal.z + z});
}

t_vec3d		plane_bump_mapping(t_vec3d normal, t_vec3d intersect
	, double epsilon)
{
	double	x;
	double	y;
	double	z;

	x = normal.x + intersect.x;
	y = normal.y * 50 + 100 * intersect.y;
	z = normal.z + intersect.z;
	return (uniform_bump_mapping((t_vec3d){x, y, z}, epsilon));
}
