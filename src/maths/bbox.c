/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:39:56 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/04 00:52:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math_utils.h"
#include "vec3d.h"

void	grow_bbox(t_vec3d *bbox_min, t_vec3d *bbox_max, t_vec3d *vertex)
{
	bbox_min->x = fmin(vertex->x, bbox_min->x);
	bbox_min->y = fmin(vertex->y, bbox_min->y);
	bbox_min->z = fmin(vertex->z, bbox_min->z);
	bbox_max->x = fmax(vertex->x, bbox_max->x);
	bbox_max->y = fmax(vertex->y, bbox_max->y);
	bbox_max->z = fmax(vertex->z, bbox_max->z);
}
