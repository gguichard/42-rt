/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:01:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/26 04:46:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vec3d.h"
#include "raytracer.h"

double			clamp(double value, double lo, double hi)
{
	if (value < lo)
		return (lo);
	else if (value > hi)
		return (hi);
	else
		return (value);
}

unsigned int	get_color_with_gamma_correction(t_vec3d color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = clamp(pow(color.x, GAMMA_CORRECTION), 0, 1) * 255;
	g = clamp(pow(color.y, GAMMA_CORRECTION), 0, 1) * 255;
	b = clamp(pow(color.z, GAMMA_CORRECTION), 0, 1) * 255;
	return ((r << 16) | (g << 8) | b);
}
