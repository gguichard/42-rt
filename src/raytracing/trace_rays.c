/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 04:54:08 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 01:39:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "ray_inf.h"
#include "ray_object.h"
#include "vec3d.h"
#include "shading.h"
#include "math_utils.h"

t_vec3d			trace_reflect_ray(t_data *data, t_ray_inf *ray_inf, int depth)
{
	t_vec3d	new_origin;
	t_vec3d	reflect_dir;

	new_origin = ray_inf->intersect;
	new_origin = vec3d_add(new_origin
			, vec3d_scalar(ray_inf->normal, SHADOW_BIAS));
	reflect_dir = vec3d_reflect(ray_inf->direction, ray_inf->normal);
	return (trace_primary_ray(data, new_origin, reflect_dir, depth - 1));
}

static double	fresnel(t_vec3d direction, t_vec3d normal, double ior)
{
	t_shading	shading;
	double		tmp;

	shading.etai = 1.0;
	shading.etat = ior;
	shading.cosi = clamp(vec3d_dot(direction, normal), -1, 1);
	if (shading.cosi > 0)
	{
		tmp = shading.etai;
		shading.etai = shading.etat;
		shading.etat = tmp;
	}
	shading.sint = shading.etai / shading.etat
		* sqrt(fmax(1 - shading.cosi * shading.cosi, 0));
	if (shading.sint >= 1)
		return (1);
	shading.cost = sqrt(fmax(1 - shading.sint * shading.sint, 0));
	shading.cosi = fabs(shading.cosi);
	shading.rs = ((shading.etat * shading.cosi) - (shading.etai * shading.cost))
		/ ((shading.etat * shading.cosi) + (shading.etai * shading.cost));
	shading.rp = ((shading.etai * shading.cosi) - (shading.etat * shading.cost))
		/ ((shading.etai * shading.cosi) + (shading.etat * shading.cost));
	return ((shading.rs * shading.rs + shading.rp * shading.rp) / 2);
}

static int		get_refract_dir(t_vec3d direction, t_vec3d normal, double ior
	, t_vec3d *refract)
{
	t_shading	shading;
	t_vec3d		ref_normal;
	double		k;
	double		tmp;

	shading.cosi = clamp(vec3d_dot(direction, normal), -1, 1);
	shading.etai = 1.0;
	shading.etat = ior;
	ref_normal = normal;
	if (shading.cosi < 0)
		shading.cosi = -shading.cosi;
	else
	{
		tmp = shading.etai;
		shading.etai = shading.etat;
		shading.etat = tmp;
		ref_normal = vec3d_scalar(ref_normal, -1);
	}
	shading.eta = shading.etai / shading.etat;
	k = 1 - shading.eta * shading.eta * (1 - shading.cosi * shading.cosi);
	if (k < 0)
		return (0);
	*refract = vec3d_add(vec3d_scalar(direction, shading.eta)
			, vec3d_scalar(ref_normal, shading.eta * shading.cosi - sqrt(k)));
	return (1);
}

t_vec3d			trace_refract_ray(t_data *data, t_ray_inf *ray_inf, int depth)
{
	t_vec3d	bias;
	t_vec3d	refract_color;
	t_vec3d	reflect_color;
	t_vec3d	refract_dir;
	double	kr;

	bias = vec3d_scalar(ray_inf->normal, SHADOW_BIAS);
	if (vec3d_dot(ray_inf->direction, ray_inf->normal) > 0)
		bias = vec3d_scalar(bias, -1);
	refract_color = vec3d(0, 0, 0);
	kr = fresnel(ray_inf->direction, ray_inf->normal
			, ray_inf->object->refractive);
	if (kr < 1 && get_refract_dir(ray_inf->direction, ray_inf->normal
			, ray_inf->object->refractive, &refract_dir))
	{
		refract_color = trace_primary_ray(data
				, vec3d_sub(ray_inf->intersect, bias), refract_dir, depth - 1);
	}
	reflect_color = trace_primary_ray(data, vec3d_add(ray_inf->intersect, bias)
			, vec3d_reflect(ray_inf->direction, ray_inf->normal), depth - 1);
	return (vec3d_add(vec3d_scalar(refract_color, 1 - kr)
			, vec3d_scalar(reflect_color, kr)));
}
