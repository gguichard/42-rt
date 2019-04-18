/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 09:00:42 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/18 10:06:54 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

double		vector_length_exp_2(t_vec3d vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3d	vector_add(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){vec1.x + vec2.x, vec1.y + vec2.y
		, vec1.z + vec2.z});
}

t_vec3d	vector_sub(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){vec1.x - vec2.x, vec1.y - vec2.y
		, vec1.z - vec2.z});
}

t_vec3d	vector_mult_by_scal(double scal, t_vec3d vec)
{
	return ((t_vec3d){vec.x * scal, vec.y * scal, vec.z * scal});
}

t_vec3d	unit_vec3d(t_vec3d vec)
{
	double		norme;

	norme = sqrt(vector_length_exp_2(vec));
	return ((t_vec3d)({vec.x / norme, vec.y / norme, vec.z / norme}));
}
