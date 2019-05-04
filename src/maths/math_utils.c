/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:01:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 17:29:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math_utils.h"
#include "vec3d.h"

void			swap_f(double *ptr1, double *ptr2)
{
	double	tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

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
