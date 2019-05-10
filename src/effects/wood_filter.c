/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wood_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 02:29:27 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/10 17:20:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "effects.h"
#include "vec3d.h"

t_vec3d	wood_filter(t_vec3d intersect, t_vec3d color1, t_vec3d color2)
{
	double		result;
	double		tmp;

	result = 20 * perlin_noise(intersect, 0);
	result = fabs(result - (int)result);
	tmp = (1 - cos(result * M_PI)) * 0.5;
	return (vec3d_add(vec3d_scalar(color1, 1 - tmp)
			, vec3d_scalar(color2, tmp)));
}
