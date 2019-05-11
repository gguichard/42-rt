/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_solid_geo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 20:17:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/10 21:46:15 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ray_object.h"

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

static void		world_to_object_transform2(t_ray_object *object, t_ray_hit *hit)
{
	hit->origin = vec3d_sub(hit->origin, object->origin);
	hit->origin = quat_rot_with_quat(hit->origin, object->rot_quat);
	hit->direction = quat_rot_with_quat(hit->direction, object->rot_quat);
	hit->direction = vec3d_unit(hit->direction);
}

void			hit_with_csg(t_ray_object *object, t_ray_hit *hit)
{
	t_ray_hit	hit1;
	t_ray_hit	hit2;

	ft_memset(&hit1, 0, sizeof(t_ray_hit));
	ft_memset(&hit2, 0, sizeof(t_ray_hit));
	hit1.direction = hit->direction;
	hit1.origin = hit->origin;
	hit2.direction = hit->direction;
	hit2.origin = hit->origin;
	world_to_object_transform2(object->csg_tree.left, &hit1);
	object->csg_tree.left->hit_fn(object->csg_tree.left, &hit1);
	world_to_object_transform2(object->csg_tree.right, &hit2);
	object->csg_tree.right->hit_fn(object->csg_tree.right, &hit2);
	if (object->csg_tree.type == CSG_UNION)
	{
		hit->dist = chose_min_between_values(hit1.dist, hit2.dist);
		hit->dist_b = chose_max_between_values(hit1.dist_b, hit2.dist_b);
		hit->normal = (hit->dist == hit1.dist ? hit1.normal : hit2.normal);
		hit->normal_b = (hit->dist_b == hit1.dist_b ? hit1.normal_b
				: hit2.normal_b);
	}
	else if (object->csg_tree.type == CSG_SUB)
		csg_sub_func(hit1, hit2, hit);
	else if (object->csg_tree.type == CSG_INTER)
		csg_inter_func(hit1, hit2, hit);
}
