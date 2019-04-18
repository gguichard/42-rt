/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:24:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 17:13:20 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rayobject.h"
#include "camera.h"

double	get_sphere_intersect(t_camera *camera, t_vec3d ray_dir
		, t_ray_object *obj)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = pow(ray_dir.x, 2) + pow(ray_dir.y, 2) + pow(ray_dir.z, 2);
	b = 2 * (ray_dir.x * (camera->origin.x - obj->origin.x)
			+ ray_dir.y * (camera->origin.y - obj->origin.y)
			+ ray_dir.z * (camera->origin.z - obj->origin.z));
	c = (pow(camera->origin.x - obj->origin.x, 2)
			+ pow(camera->origin.y - obj->origin.y, 2)
			+ pow(camera->origin.z - obj->origin.z, 2))
		- pow(obj->radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		double t1 = (-b + sqrt(delta)) / (2 * a);
		double t2 = (delta == 0 ? t1 : (-b - sqrt(delta)) / (2 * a));
		if (t1 >= 0 && t2 >= 0)
			return (t1 < t2 ? t1 : t2);
		else if (t1 >= 0 && t2 < 0)
			return (t1);
		else if (t1 < 0 && t2 >= 0)
			return (t2);
	}
	return (-1);
}
