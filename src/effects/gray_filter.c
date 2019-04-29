/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:46:31 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/29 01:47:22 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "vec3d.h"

t_vec3d		gray_filter(t_vec3d color)
{
	double	c;

	c = pow(((color.x + color.y + color.z) / 3.0), 1 / GAMMA_CORRECTION);
	return ((t_vec3d){c, c, c});
}
