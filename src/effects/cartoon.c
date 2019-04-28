/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:15:01 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/28 17:15:49 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perturbations.h"
#include "vec3d.h"

t_vec3d		cartoon_effect_filter(t_vec3d color, t_vec3d init_color)
{
	double		init_c;
	double		c;

	init_c = (init_color.x + init_color.y + init_color.z) / 3.0;
	c = ((color.x + color.y + color.z) / 3.0 + init_c) / 2.0;
	if (c >= 0.5)
		return (init_color);
	if (c >= 0.25)
		return (vec3d_scalar(init_color, 0.75));
	return ((t_vec3d){0, 0, 0});
}
