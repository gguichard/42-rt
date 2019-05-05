/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gray_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:46:31 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/06 01:34:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3d.h"
#include "math_utils.h"

t_vec3d	gray_filter(t_vec3d color)
{
	double	c;

	c = pow((color.x + color.y + color.z) / 3.0, 1.0 / GAMMA_CORRECTION);
	return (vec3d(c, c, c));
}
