/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:02:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/21 03:22:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

unsigned int	color_get_rgb(t_color color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = color.r * 255;
	g = color.g * 255;
	b = color.b * 255;
	return ((r << 16) | (g << 8) | b);
}

t_color			color_create_from_rgb(int rgb)
{
	t_color	new_color;

	new_color.r = ((rgb >> 16) & 0xFF) / 255.;
	new_color.g = ((rgb >> 8) & 0xFF) / 255.;
	new_color.b = (rgb & 0xFF) / 255.;
	return (new_color);
}

t_color			color_clamp(t_color color)
{
	t_color	new_color;

	new_color.r = (color.r > 1. ? 1. : color.r);
	new_color.g = (color.g > 1. ? 1. : color.g);
	new_color.b = (color.b > 1. ? 1. : color.b);
	return (new_color);
}

t_color			color_add(t_color color_a, t_color color_b)
{
	t_color	new_color;

	new_color.r = color_a.r + color_b.r;
	new_color.g = color_a.g + color_b.g;
	new_color.b = color_a.b + color_b.b;
	return (new_color);
}

t_color			color_mul(t_color color_a, t_color color_b)
{
	t_color	new_color;

	new_color.r = color_a.r * color_b.r;
	new_color.g = color_a.g * color_b.g;
	new_color.b = color_a.b * color_b.b;
	return (new_color);
}

t_color			color_scalar(t_color color, float scalar)
{
	t_color	new_color;

	new_color.r = color.r * scalar;
	new_color.g = color.g * scalar;
	new_color.b = color.b * scalar;
	return (new_color);
}
