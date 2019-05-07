/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 23:39:06 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 02:42:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "effects.h"
#include "vec3d.h"

static double	fade(double nbr)
{
	return (pow(nbr, 3) * (nbr * (nbr * 6 - 15) + 10));
}

static double	linear_interpolation(double nbr, double x, double y)
{
	return (x + nbr * (y - x));
}

static double	gradient(int hash, double x, double y, double z)
{
	int		compare;
	double	orient_x;
	double	orient_y;

	compare = hash & 15;
	orient_x = (compare < 8 ? x : y);
	if (compare < 4)
		orient_y = y;
	else
		orient_y = (compare == 12 || compare == 14 ? x : z);
	orient_x *= (compare & 1 ? -1 : 1);
	orient_y *= (compare & 2 ? -1 : 1);
	return (orient_x + orient_y);
}

static double	perlin_result(t_perlin perlin, t_vec3d intersect)
{
	perlin.result = linear_interpolation(perlin.w, linear_interpolation(perlin.v
				, linear_interpolation(perlin.u, gradient(
						perlin.permut[perlin.hash[2]], intersect.x
						, intersect.y, intersect.z), gradient(
						perlin.permut[perlin.hash[4]], intersect.x - 1
						, intersect.y, intersect.z))
				, linear_interpolation(perlin.u, gradient(
						perlin.permut[perlin.hash[3]], intersect.x, intersect.y
						- 1, intersect.z), gradient(
						perlin.permut[perlin.hash[5]], intersect.x - 1
						, intersect.y - 1, intersect.z))), linear_interpolation(
				perlin.v, linear_interpolation(perlin.u, gradient(
						perlin.permut[perlin.hash[2] + 1], intersect.x
						, intersect.y, intersect.z - 1), gradient(
						perlin.permut[perlin.hash[4] + 1], intersect.x - 1
						, intersect.y, intersect.z - 1))
				, linear_interpolation(perlin.u, gradient(
					perlin.permut[perlin.hash[3] + 1], intersect.x
					, intersect.y - 1, intersect.z - 1), gradient(
					perlin.permut[perlin.hash[5] + 1], intersect.x - 1
					, intersect.y - 1, intersect.z - 1))));
	return (perlin.result);
}

double			perlin_noise(t_vec3d intersect, int type)
{
	t_perlin	perlin;

	ft_memset(&perlin, 0, sizeof(t_perlin));
	if (type == 1)
		perlin_random_permutation(&perlin);
	else
		perlin_basic_permutation(&perlin);
	perlin.x = (int)floor(intersect.x) & 255;
	perlin.y = (int)floor(intersect.y) & 255;
	perlin.z = (int)floor(intersect.z) & 255;
	intersect.x -= floor(intersect.x);
	intersect.y -= floor(intersect.y);
	intersect.z -= floor(intersect.z);
	perlin.u = fade(intersect.x);
	perlin.v = fade(intersect.y);
	perlin.w = fade(intersect.z);
	perlin.hash[0] = perlin.permut[perlin.x] + perlin.y;
	perlin.hash[1] = perlin.permut[perlin.x + 1] + perlin.y;
	perlin.hash[2] = perlin.permut[perlin.hash[0]] + perlin.z;
	perlin.hash[3] = perlin.permut[perlin.hash[0] + 1] + perlin.z;
	perlin.hash[4] = perlin.permut[perlin.hash[1]] + perlin.z;
	perlin.hash[5] = perlin.permut[perlin.hash[1] + 1] + perlin.z;
	return (perlin_result(perlin, intersect));
}
