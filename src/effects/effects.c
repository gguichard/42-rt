/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 00:27:20 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/05 20:22:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"
#include "raytracer.h"
#include "ray_inf.h"
#include "vec3d.h"

t_vec3d	apply_effects(t_data *data, t_ray_inf *ray_inf, t_vec3d color
	, t_vec3d init_color)
{
	if (data->effect == GRAY_FILTER)
		color = gray_filter(color);
	else if (data->effect == CARTOON_FILTER)
		color = cartoon_filter(color, init_color);
	if (data->fog != 0)
		color = apply_fog_effect(data, ray_inf, color);
	return (color);
}
