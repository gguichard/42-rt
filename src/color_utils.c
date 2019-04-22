/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:37:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 21:38:02 by gguichar         ###   ########.fr       */
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
