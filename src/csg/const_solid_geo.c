/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_solid_geo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 20:17:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/08 16:03:26 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ray_object.h"

t_tree_csg	*create_node(t_ray_object *object, int type)
{
	t_tree_csg	*new_elem;

	if (!(new_elem = (t_tree_csg*)malloc(sizeof(t_tree_csg))))
		return (NULL);
	new_elem->type = type;
	new_elem->object = object;
	new_elem->first = NULL;
	new_elem->second = NULL;
	return (new_elem);
}

static double	chose_min_between_values(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	if (a < 0)
		return (b);
	if (b < 0)
		return (a);
	return (a > b ? b : a);
}

static double	chose_max_between_values(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	if (a < 0)
		return (b);
	if (b < 0)
		return (a);
	return (a > b ? a : b);
}

void		csg_sub_func(t_tree_csg *tree, t_ray_hit hit1, t_ray_hit hit2
	, t_ray_hit *hit)
{
	if (hit2.dist == -1 && hit2.dist_b == -1)
		*hit = hit1;
	else if (hit2.dist <= hit1.dist)
	{
		if (hit2.dist_b > hit1.dist && hit2.dist_b < hit1.dist_b)
		{
			hit->dist = hit2.dist_b;
			hit->dist_b = hit1.dist_b;
			hit->normal = hit2.normal_b;
			hit->normal_b = hit1.normal_b;
		}
		else if (hit2.dist_b > hit1.dist_b)
		{
			hit->dist = -1;
			hit->dist_b = -1;
		}
		else
			*hit = hit1;
	}
	else if (hit2.dist > hit1.dist)
	{
		if (hit2.dist > hit1.dist_b || hit2.dist_b < hit1.dist_b)
			*hit = hit1;
		else if (hit2.dist_b > hit2.dist_b)
		{
			hit->dist = hit1.dist;
			hit->dist.b = hit2.dist;
			hit->normal = hit1.normal;
			hit->normal_b = hit1.normal_b;
		}
	}
}

void		csg_inter_func(t_tree_csg *tree, t_ray_hit hit1, t_ray_hit hit2
	, t_ray_hit *hit)
{
	if ((hit2.dist == -1 && hit2.dist_b == -1)
		|| (hit1.dist == -1 && hit1.dist_b == -1))
	{
		hit->dist = -1;
		hit->dist_b = -1;
	}
	else if (hit1.dist > 0)
	{
		if (hit2.dist_b < hit1.dist || hit2.dist_b > hit1.dist_b)
		{
			hit->dist = -1;
			hit->dist_b = -1;
		}
		else if (hit2.dist <= hit1.dist && hit2.dist_b >= hit1.dist
			&& hit2.dist_b <= hit1.dist_b)
		{
			hit->dist = hit1.dist;
			hit->dist_b = hit2.dist_b;
			hit->normal = hit1.normal;
			hit->normal_b = hit2.normal_b;
		}
		else if (hit2.dist <= hit1.dist && hit2.dist_b >= hit1.dist_b)
			*hit = hit1;
		else if (hit2.dist >= hit1.dist && hit2.dist_b <= hit1.dist_b)
			*hit = hit2;
		else if (hit2.dist >= hit1.dist && hit2.dist <= hit1.dist_b
			&& hit2.dist_b >= hit1.dist_b)
		{
			hit->dist = hit2.dist;
			hit->dist_b = hit1.dist_b;
			hit->normal = hit2.normal;
			hit->normal_b = hit1.dist_b;
		}
	}
	else if (hit1.dist_b > 0)
	{
		if (hit2.dist_b < 0 || hit2.dist > hit1.dist_b)
		{
			hit->dist = -1;
			hit->dist_b = -1;
		}
		else if (hit2.dist <= 0 && hit2.dist_b >= 0
			&& hit2.dist_b <= hit1.dist_b)
		{
			hit->dist = hit2.dist_b;
			hit->dist_b = -1;
			hit->normal = hit2.normal_b;
		}
		else if (hit2.dist <= 0 && hit2.dist_b >= hit1.dist_b)
		{
			hit->dist = hit1.dist_b;
			hit->dist_b = -1;
			hit->normal = hit1.dist_b;
		}
		else if (hit2.dist >= 0 && hit2.dist_b <= hit1.dist_b)
			*hit = hit2;
		else if (hit2.dist >= 0 && hit2.dist_b >= hit1.dist_b)
		{
			hit->dist = hit2.dist;
			hit->dist_b = hit1.dist_b;
			hit->normal = hit2.normal;
			hit->normal_b = hit1.normal_b;
		}
	}
	else
	{
		hit->dist = -1;
		hit->dist_b = -1;
	}
}

void		hit_with_csg(t_tree_csg *tree, t_ray_hit *hit)
{
	t_ray_hit	hit1;
	t_ray_hit	hit2;

	ft_memset(&hit1, 0, sizeof(t_ray_hit));
	ft_memset(&hit2, 0, sizeof(t_ray_hit));
	hit1.direction = hit->direction;
	hit1.origin = hit->origin;
	hit2.direction = hit->direction;
	hit2.origin = hit->origin;
	if (tree->first->type == CSG_OBJECT)
		tree->first->object->hit_fn(tree->first->object, &hit1);
	else
		hit_with_csg(tree->first, &hit1);
	if (tree->second->type == CSG_OBJECT)
		tree->second->object->hit_fn(tree->second->object, &hit2);
	else
		hit_with_csg(tree->second, &hit2);
	if (tree->type == CSG_UNION)
	{
		hit->dist = chose_min_between_values(hit1.dist, hit2.dist);
		hit->dist_b = chose_max_between_values(hit1.dist_b, hit2.dist_b);
		hit->normal = (hit->dist == hit1.dist ? hit1.normal : hit2.normal);
		hit->normal_b = (hit->dist_b == hit1.dist_b ? hit1.normal_b
				: hit2.normal_b);
	}
	if (tree->type == CSG_SUB)
		csg_sub_func(tree, hit1, hit2, hit);
	if (tree->type == CSG_INTER)
		csg_inter_func(tree, hit1, hit2, hit);
}
