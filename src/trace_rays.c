/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 04:54:08 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/25 18:57:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "ray_inf.h"
#include "ray_object.h"
#include "vec3d.h"

unsigned int	trace_reflect_ray(t_data *data, t_ray_inf *ray_inf, int depth)
{
	t_vec3d	new_origin;
	t_vec3d	reflect_dir;

	new_origin = ray_inf->intersect;
	new_origin = vec3d_add(new_origin
			, vec3d_scalar(ray_inf->normal, SHADOW_BIAS));
	reflect_dir = vec3d_reflect(ray_inf->direction, ray_inf->normal);
	return (trace_primary_ray(data, new_origin, reflect_dir, depth - 1));
}

/*double			fresnel(t_vec3d *direction, t_vec3d *normal, double ior)
  {
  double	cosi;

  cosi = vec3d_dot(direction, normal);
  if (cosi < 0)
  cosi = -cosi;

  }*/

static t_vec3d	get_refract_dir(t_ray_inf *ray_inf, t_vec3d normal_refract
		, double n1, double n2)
{
	double	radical;
	t_vec3d	refract_dir;

	radical = 1 - pow(n1 / n2, 2)
		* (1 - pow(vec3d_dot(normal_refract, ray_inf->direction), 2));
	if (radical > .0)
	{
		refract_dir = vec3d_scalar(normal_refract
				, vec3d_dot(ray_inf->direction, normal_refract));
		refract_dir = vec3d_scalar(vec3d_sub(ray_inf->direction, refract_dir)
				, n1 / n2);
		refract_dir = vec3d_sub(refract_dir
				, vec3d_scalar(normal_refract, sqrt(radical)));
		return (refract_dir);
	}
	return ((t_vec3d){.0, .0, .0});
}

unsigned int	trace_refract_ray(t_data *data, t_ray_inf *ray_inf, int depth)
{
	double	n1;
	double	n2;
	t_vec3d	normal_refract;
	t_vec3d	refract_dir;

	n1 = 1.0;
	n2 = ray_inf->object->refractive;
	normal_refract = ray_inf->normal;
	if (vec3d_dot(ray_inf->direction, ray_inf->normal) > 0)
	{
		n1 = ray_inf->object->refractive;
		n2 = 1.0;
		normal_refract = vec3d_scalar(normal_refract, -1);
	}
	refract_dir = get_refract_dir(ray_inf, normal_refract, n1, n2);
	if (refract_dir.x != .0 || refract_dir.y != .0 || refract_dir.z != .0)
	{
		return (trace_primary_ray(data, vec3d_sub(ray_inf->intersect
						, vec3d_scalar(normal_refract, SHADOW_BIAS))
					, refract_dir, depth - 1));
	}
	return (0x0);
}
