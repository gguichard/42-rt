/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_filter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 01:51:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/05 20:22:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"
#include "vec3d.h"

t_vec3d	perlin_noise_filter(t_vec3d intersect, t_vec3d color1, t_vec3d color2
	, t_vec3d color3)
{
	double	result;

	result = perlin_noise(intersect, 0);
	if (result <= 0.15)
		return (color1);
	else if (result <= 0.55)
		return (color2);
	else
		return (color3);
}
