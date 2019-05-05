/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:30:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 01:34:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "effects.h"
#include "raytracer.h"
#include "ray_inf.h"
#include "vec3d.h"

t_vec3d	apply_fog_effect(t_data *data, t_ray_inf *ray_inf, t_vec3d color)
{
	double	fog_scalar;

	fog_scalar = exp(-pow(ray_inf->dist / data->fog, 2));
	return (vec3d_add(vec3d_scalar(vec3d(1, 1, 1), 1 - fog_scalar)
			, vec3d_scalar(color, fog_scalar)));
}
