/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:40:54 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 13:09:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "quaternion.h"

# define CSGACTION_MISS (1 << 0)
# define CSGACTION_RETLIFCLOSER (1 << 1)
# define CSGACTION_RETLIFFARTHER (1 << 2)
# define CSGACTION_RETL (1 << 3)
# define CSGACTION_RETRIFCLOSER (1 << 4)
# define CSGACTION_RETRIFFARTHER (1 << 5)
# define CSGACTION_RETR (1 << 6)
# define CSGACTION_FLIPR (1 << 7)
# define CSGACTION_LOOPL (1 << 8)
# define CSGACTION_LOOPR (1 << 9)
# define CSGACTION_LOOPLIFCLOSER (1 << 10)
# define CSGACTION_LOOPRIFCLOSER (1 << 10)

# define HIT_ENTER 0
# define HIT_EXIT 1
# define HIT_MISS 2

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

static int	classify_hit_type(t_ray_object *object, t_ray_hit *hit)
{
	double	cosine_angle;

	hit->normal = quat_rot_with_quat(hit->normal, object->inv_rot_quat);
	if (hit->dist < hit->min_dist)
		return (HIT_MISS);
	cosine_angle = vec3d_dot(hit->direction, hit->normal);
	if (cosine_angle < .0)
		return (HIT_ENTER);
	else
		return (HIT_EXIT);
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
		hit_type_left = classify_hit_type(object->csg_tree.left, &hit_left);
		hit_type_right = classify_hit_type(object->csg_tree.right, &hit_right);
		actions = table[hit_type_left][hit_type_right];
		if (actions & CSGACTION_MISS)
			break ;
		else if (actions & CSGACTION_RETL
			|| (actions & CSGACTION_RETLIFCLOSER && hit_left.dist <= hit_right.dist)
			|| (actions & CSGACTION_RETLIFFARTHER && hit_left.dist > hit_right.dist))
		{
			hit->dist = hit_left.dist;
			hit->normal = hit_left.normal;
			break ;
		}
		else if (actions & CSGACTION_RETR
			|| (actions & CSGACTION_RETRIFCLOSER && hit_right.dist <= hit_left.dist)
			|| (actions & CSGACTION_RETRIFFARTHER && hit_right.dist > hit_left.dist))
		{
			if (actions & CSGACTION_FLIPR)
				hit_right.normal = vec3d_scalar(hit_right.normal, -1);
			hit->dist = hit_right.dist;
			hit->normal = hit_right.normal;
			break ;
		}
		else if (actions & CSGACTION_LOOPL
			|| (actions & CSGACTION_LOOPLIFCLOSER && hit_left.dist <= hit_right.dist))
		{
			hit_left.min_dist = hit_left.dist + 1e-6;
			hit_left.dist = -INFINITY;
			object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_left);
		}
		else if (actions & CSGACTION_LOOPR
			|| (actions & CSGACTION_LOOPRIFCLOSER && hit_right.dist <= hit_left.dist))
		{
			hit_right.min_dist = hit_right.dist + 1e-6;
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
}
