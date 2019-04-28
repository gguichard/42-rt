/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sin_perturbation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:13:59 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/28 17:11:07 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3d.h"

t_vec3d		normal_sin_perturbation(t_vec3d normal)
{
	double		tmp;

	tmp = sin(normal.x);
	normal.x *= (tmp + normal.x);
	tmp = cos(normal.y);
	normal.y *= (tmp + normal.y);
	tmp = -sin(normal.z);
	normal.z *= (tmp + normal.z);
	return (vec3d_unit(normal));
}
