/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:24:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 20:21:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "camera.h"
#include "calcul.h"
#include "libft.h"

double	get_sphere_intersect(t_camera *camera, t_vec3d ray_dir
		, t_ray_object *obj)
{
	t_calcul	calc;

	ft_memset(&calc, 0, sizeof(t_calcul));
	calc.tmp1 = camera->origin.x - obj->origin.x;
	calc.tmp2 = camera->origin.y - obj->origin.y;
	calc.tmp3 = camera->origin.z - obj->origin.z;
	calc.a = pow(ray_dir.x, 2) + pow(ray_dir.y, 2) + pow(ray_dir.z, 2);
	calc.b = 2 * (ray_dir.x * calc.tmp1 + ray_dir.y * calc.tmp2
			+ ray_dir.z * calc.tmp3);
	calc.c = (pow(calc.tmp1, 2) + pow(calc.tmp2, 2) + pow(calc.tmp3, 2))
		- pow(obj->radius, 2);
	calc.delta = pow(calc.b, 2) - 4 * calc.a * calc.c;
	if (calc.delta >= 0)
	{
		calc.a = 2 * calc.a;
		calc.tmp3 = sqrt(calc.delta);
		calc.tmp1 = (calc.tmp3 - calc.b) / (calc.a);
		calc.tmp2 = (calc.delta == 0 ? calc.tmp1
				: (-calc.b - calc.tmp3) / (calc.a));
		if (calc.tmp1 >= 0 && calc.tmp2 >= 0)
			return (calc.tmp1 < calc.tmp2 ? calc.tmp1 : calc.tmp2);
		else if (calc.tmp1 >= 0 && calc.tmp2 < 0)
			return (calc.tmp1);
		else if (calc.tmp1 < 0 && calc.tmp2 >= 0)
			return (calc.tmp2);
	}
	return (-1);
}
