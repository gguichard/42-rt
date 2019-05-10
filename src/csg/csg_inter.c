/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 20:03:27 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/10 19:32:22 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_object.h"
#include "vec3d.h"

void		csg_inter_func(t_ray_hit hit1, t_ray_hit hit2, t_ray_hit *hit)
{
	if (hit1.dist <= 0 || hit2.dist <= 0)
	{
		hit->dist = -1;
		hit->dist_b = -1;
	}
	else if (hit1.dist == hit1.dist_b)
	{
		if (hit2.dist == hit2.dist_b)
		{
			if (hit2.dist < hit1.dist)
			{
				hit->dist = hit2.dist;
				hit->normal = hit2.normal;
				hit->dist_b = -1;
			}
			else
			{
				hit->dist = hit1.dist;
				hit->normal = hit1.normal;
				hit->dist_b = hit2.dist;
				hit->normal_b = hit2.normal;
			}
		}
		else
		{
			if (hit2.dist < hit1.dist && hit2.dist_b < hit1.dist)
				*hit = hit2;
			else if (hit2.dist < hit1.dist)
			{
				hit->dist = hit2.dist;
				hit->normal = hit2.normal;
				hit->dist_b = hit1.dist;
				hit->normal_b = hit1.normal;
			}
			else
			{
				hit->dist = -1;
				hit->dist_b = -1;
			}
		}
	}
	else
	{
		if (hit2.dist == hit2.dist_b)
		{
			if (hit2.dist <= hit1.dist)
			{
				hit->dist = -1;
				hit->dist_b = -1;
			}
			else if (hit2.dist > hit1.dist && hit2.dist < hit1.dist_b)
			{
				hit->dist = hit1.dist;
				hit->normal = hit1.normal;
				hit->dist_b = hit2.dist;
				hit->normal_b = hit2.normal;
			}
			else
				*hit = hit1;
		}
		else
		{
			if (hit2.dist_b < hit1.dist || hit2.dist >= hit1.dist_b)
			{
				hit->dist = -1;
				hit->dist_b = -1;
			}
			else if (hit1.dist < hit2.dist && hit2.dist_b > hit1.dist_b)
			{
				hit->dist = hit2.dist;
				hit->normal = hit2.normal;
				hit->dist_b = hit1.dist_b;
				hit->normal_b = hit1.normal_b;
			}
			else if (hit2.dist < hit1.dist &&  hit2.dist_b < hit1.dist_b)
			{
				hit->dist = hit1.dist;
				hit->normal = hit1.normal;
				hit->dist_b = hit2.dist_b;
				hit->normal_b = hit2.normal_b;
			}
			else if (hit2.dist_b < hit1.dist_b)
				*hit = hit2;
			else
				*hit = hit1;
		}
	}
}
