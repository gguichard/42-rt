/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:40:54 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/12 01:29:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "quaternion.h"
#include "csg.h"

const int	g_csg_union[3][3] = {
	{CSGACTION_RETLIFCLOSER | CSGACTION_RETRIFCLOSER
		, CSGACTION_RETRIFCLOSER | CSGACTION_LOOPL, CSGACTION_RETL}
	, {CSGACTION_RETLIFCLOSER | CSGACTION_LOOPR
		, CSGACTION_RETLIFFARTHER | CSGACTION_RETRIFFARTHER, CSGACTION_RETL}
	, {CSGACTION_RETR, CSGACTION_RETR, CSGACTION_MISS}
};

const int	g_csg_inter[3][3] = {
	{CSGACTION_LOOPLIFCLOSER | CSGACTION_LOOPRIFCLOSER
		, CSGACTION_RETLIFCLOSER | CSGACTION_LOOPR, CSGACTION_MISS}
	, {CSGACTION_RETRIFCLOSER | CSGACTION_LOOPL
		, CSGACTION_RETLIFCLOSER | CSGACTION_RETRIFCLOSER, CSGACTION_MISS}
	, {CSGACTION_MISS, CSGACTION_MISS, CSGACTION_MISS}
};

const int	g_csg_sub[3][3] = {
	{CSGACTION_RETLIFCLOSER | CSGACTION_LOOPR
		, CSGACTION_LOOPLIFCLOSER | CSGACTION_LOOPRIFCLOSER, CSGACTION_RETL}
	, {CSGACTION_RETLIFCLOSER | CSGACTION_RETRIFCLOSER | CSGACTION_FLIPR
		, CSGACTION_RETRIFCLOSER | CSGACTION_FLIPR | CSGACTION_LOOPL
			, CSGACTION_RETL}
	, {CSGACTION_MISS, CSGACTION_MISS, CSGACTION_MISS}
};

static void	setup_csg_hit(t_ray_hit *hit, t_ray_object *object
	, t_ray_hit *par_hit)
{
	hit->origin = vec3d_sub(par_hit->origin, object->origin);
	hit->origin = quat_rot_with_quat(hit->origin, object->rot_quat);
	hit->direction = quat_rot_with_quat(par_hit->direction, object->rot_quat);
	hit->direction = vec3d_unit(hit->direction);
	hit->min_dist = .0;
	hit->dist = -INFINITY;
}

static int	classify_hit_type(t_ray_hit *hit)
{
	double	cosine_angle;

	if (hit->dist <= hit->min_dist)
		return (CSGHIT_MISS);
	cosine_angle = vec3d_dot(hit->direction, hit->normal);
	if (cosine_angle < .0)
		return (CSGHIT_ENTER);
	else
		return (CSGHIT_EXIT);
}

static void	hit_csg_actions(t_ray_object *object, t_ray_hit *hit
	, const int table[3][3])
{
	t_ray_hit	hit_left;
	t_ray_hit	hit_right;
	int			hit_type_left;
	int			hit_type_right;
	int			actions;

	setup_csg_hit(&hit_left, object->csg_tree.left, hit);
	setup_csg_hit(&hit_right, object->csg_tree.right, hit);
	object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_left);
	object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_right);
	while (1)
	{
		hit_type_left = classify_hit_type(&hit_left);
		hit_type_right = classify_hit_type(&hit_right);
		actions = table[hit_type_left][hit_type_right];
		if (actions & CSGACTION_MISS)
			break ;
		else if (actions & CSGACTION_RETL
			|| (actions & CSGACTION_RETLIFCLOSER
				&& hit_left.dist <= hit_right.dist)
			|| (actions & CSGACTION_RETLIFFARTHER
				&& hit_left.dist > hit_right.dist))
		{
			hit->dist = hit_left.dist;
			hit->normal = vec3d_unit(quat_rot_with_quat(hit_left.normal
						, object->csg_tree.left->inv_rot_quat));
			break ;
		}
		else if (actions & CSGACTION_RETR
			|| (actions & CSGACTION_RETRIFCLOSER
				&& hit_right.dist <= hit_left.dist)
			|| (actions & CSGACTION_RETRIFFARTHER
				&& hit_right.dist > hit_left.dist))
		{
			if (actions & CSGACTION_FLIPR)
				hit_right.normal = vec3d_scalar(hit_right.normal, -1);
			hit->dist = hit_right.dist;
			hit->normal = vec3d_unit(quat_rot_with_quat(hit_right.normal
						, object->csg_tree.right->inv_rot_quat));
			break ;
		}
		else if (actions & CSGACTION_LOOPL
			|| (actions & CSGACTION_LOOPLIFCLOSER
				&& hit_left.dist <= hit_right.dist))
		{
			hit_left.min_dist = hit_left.dist;
			hit_left.dist = -INFINITY;
			object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_left);
		}
		else if (actions & CSGACTION_LOOPR
			|| (actions & CSGACTION_LOOPRIFCLOSER
				&& hit_right.dist <= hit_left.dist))
		{
			hit_right.min_dist = hit_right.dist;
			hit_right.dist = -INFINITY;
			object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_right);
		}
		else
			break ;
	}
}

void		hit_csg(t_ray_object *object, t_ray_hit *hit)
{
	if (object->type == RAYOBJ_CSGUNION)
		hit_csg_actions(object, hit, g_csg_union);
	else if (object->type == RAYOBJ_CSGINTER)
		hit_csg_actions(object, hit, g_csg_inter);
	else if (object->type == RAYOBJ_CSGSUB)
		hit_csg_actions(object, hit, g_csg_sub);
	if (hit->dist <= hit->min_dist)
		hit->dist = -INFINITY;
}
