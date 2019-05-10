/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 20:03:27 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/10 15:18:16 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_object.h"
#include "vec3d.h"

static void	csg_sub_utils_2(t_ray_hit hit1, t_ray_hit hit2, t_ray_hit *hit
	, int type)
{
	if (type == 0)
	{
		hit->dist = hit2.dist_b;
		hit->normal = hit2.normal_b;
		hit->dist_b = hit1.dist_b;
		hit->normal_b = hit1.normal_b;
	}
	else
	{
		hit->dist = -1;
		hit->dist_b = -1;
	}
}

static void	csg_sub_utils(t_ray_hit hit1, t_ray_hit hit2, t_ray_hit *hit)
{
	hit->dist = hit2.dist;
	hit->normal = hit2.normal;
	hit->dist_b = hit1.dist_b;
	hit->normal_b = hit1.normal_b;
}

static void	csg_sub_func_2(t_ray_hit hit1, t_ray_hit hit2, t_ray_hit *hit)
{
	if (hit2.dist <= 0)
	{
		hit->dist = hit1.dist;
		hit->normal = hit1.normal;
		hit->dist_b = -1;
	}
	else if (hit2.dist == hit2.dist_b)
	{
		if (hit2.dist < hit1.dist_b)
			csg_sub_utils(hit1, hit2, hit);
		else
		{
			hit->dist = -1;
			hit->dist_b = -1;
		}
	}
	else if (hit2.dist > hit1.dist && hit2.dist <= hit1.dist_b)
	{
		if (hit2.dist_b < hit1.dist_b)
			*hit = hit1;
		else
			*hit = hit2;
	}
	else
		*hit = hit1;
}

static void	csg_sub_func_3(t_ray_hit hit1, t_ray_hit hit2, t_ray_hit *hit)
{
	if (hit2.dist < hit1.dist && hit2.dist_b < hit2.dist_b)
		csg_sub_utils_2(hit1, hit2, hit, 0);
	else if (hit2.dist < hit1.dist)
		csg_sub_utils_2(hit1, hit2, hit, 1);
	else if (hit2.dist < hit1.dist_b && hit2.dist_b < hit2.dist_b)
		*hit = hit1;
	else if (hit2.dist < hit1.dist_b)
	{
		hit->dist = hit1.dist;
		hit->normal = hit1.normal;
		hit->dist_b = hit2.dist;
		hit->normal_b = hit2.normal;
	}
	else
		*hit = hit1;
}

void		csg_sub_func(t_ray_hit hit1, t_ray_hit hit2, t_ray_hit *hit)
{
	if (hit1.dist <= 0)
		csg_sub_utils_2(hit1, hit2, hit, 1);
	else if (hit1.dist == hit1.dist_b)
		csg_sub_func_2(hit1, hit2, hit);
	else
	{
		if (hit2.dist < hit1.dist && hit2.dist_b < hit1.dist)
			*hit = hit1;
		else if (hit2.dist < hit1.dist && hit2.dist_b > hit1.dist
			&& hit2.dist_b < hit1.dist_b)
			csg_sub_utils_2(hit1, hit2, hit, 0);
		else if (hit2.dist == hit2.dist_b)
		{
			if (hit2.dist < hit1.dist_b)
				csg_sub_utils(hit1, hit2, hit);
			else
				csg_sub_utils_2(hit1, hit2, hit, 1);
		}
		else
			csg_sub_func_3(hit1, hit2, hit);
	}
}
