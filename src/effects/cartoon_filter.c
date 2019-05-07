/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon_filter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:15:01 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/06 01:34:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"
#include "vec3d.h"

t_vec3d	cartoon_filter(t_vec3d color, t_vec3d init_color)
{
	double	init_c;
	double	c;

	init_c = (init_color.x + init_color.y + init_color.z);
	c = (color.x + color.y + color.z);
	c = c / init_c;
	if (c >= 1.0)
		return (vec3d_scalar(init_color, 1.25));
	else if (c >= 0.50)
		return (init_color);
	else if (c >= 0.15)
		return (vec3d_scalar(init_color, 0.75));
	else if (c >= 0.05)
		return (vec3d_scalar(init_color, 0.50));
	else
		return (vec3d(0, 0, 0));
}
