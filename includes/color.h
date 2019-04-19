/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:41:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/19 20:16:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

unsigned int	color_get_rgb(t_color color);
t_color			color_create_from_rgb(int rgb);
t_color			color_clamp(t_color color);
t_color			color_add(t_color color_a, t_color color_b);
t_color			color_mul(t_color color, float scale);

#endif
