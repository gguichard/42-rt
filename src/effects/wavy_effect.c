/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wavy_effect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:29:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 12:43:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3d.h"

t_vec3d	wavy_perturbation(t_vec3d normal, t_vec3d intersect)
{
	normal.x += sin(intersect.x) * 0.1;
	normal.z += sin(intersect.x) * 0.1;
	return (vec3d_unit(normal));
}
