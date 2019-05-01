/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 09:00:42 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/01 16:05:21 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3d.h"

double		vec3d_length2(t_vec3d vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double		vec3d_length(t_vec3d vec)
{
	return (sqrt(vec3d_length2(vec)));
}

t_vec3d		vec3d_unit(t_vec3d vec)
{
	double	length;

	length = vec3d_length(vec);
	return ((t_vec3d){vec.x / length, vec.y / length, vec.z / length});
}

t_vec3d		vec3d_add(t_vec3d vec_a, t_vec3d vec_b)
{
	return ((t_vec3d){vec_a.x + vec_b.x, vec_a.y + vec_b.y
		, vec_a.z + vec_b.z});
}

t_vec3d		vec3d_sub(t_vec3d vec_a, t_vec3d vec_b)
{
	return ((t_vec3d){vec_a.x - vec_b.x, vec_a.y - vec_b.y
		, vec_a.z - vec_b.z});
}
