/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 00:27:20 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/29 23:17:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perturbations.h"
#include "raytracer.h"
#include "vec3d.h"

t_vec3d		apply_effects(t_data *data, t_vec3d color, t_vec3d init_color)
{
	if (data->effect == NONE_FILTER)
		return (color);
	else if (data->effect == GRAY_FILTER)
		return (gray_filter(color));
	else
		return (cartoon_filter(color, init_color));
}
