/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:40:54 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 03:13:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "quaternion.h"

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

# define HIT_MISS 0
# define HIT_ENTER 1
# define HIT_EXIT 2

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

static void	hit_csg_union(t_ray_object *object, t_ray_hit *hit)
{
	t_ray_hit	hit_a;
	t_ray_hit	hit_b;
	int			hit_type_a;
	int			hit_type_b;

	setup_csg_hit(&hit_a, object->csg_tree.left, hit);
	setup_csg_hit(&hit_b, object->csg_tree.right, hit);
	object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_a);
	object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_b);
	hit_type_a = classify_hit_type(object->csg_tree.left, &hit_a);
	hit_type_b = classify_hit_type(object->csg_tree.right, &hit_b);
	while (1)
	{
		if (hit_type_a == HIT_MISS && hit_type_b == HIT_MISS)
			break ;
		else if ((hit_type_a != HIT_MISS && hit_type_b == HIT_MISS)
			|| (hit_type_a == HIT_ENTER && hit_type_b == HIT_ENTER && hit_a.dist <= hit_b.dist)
			|| (hit_type_a == HIT_EXIT && hit_type_b == HIT_EXIT && hit_a.dist > hit_b.dist)
			|| (hit_type_a == HIT_EXIT && hit_type_b == HIT_ENTER && hit_a.dist <= hit_b.dist))
		{
			hit->dist = hit_a.dist;
			hit->normal = hit_a.normal;
			break ;
		}
		else if ((hit_type_b != HIT_MISS && hit_type_a == HIT_MISS)
			|| (hit_type_b == HIT_ENTER && hit_type_a == HIT_ENTER && hit_b.dist <= hit_a.dist)
			|| (hit_type_b == HIT_EXIT && hit_type_a == HIT_EXIT && hit_b.dist > hit_a.dist)
			|| (hit_type_b == HIT_EXIT && hit_type_a == HIT_ENTER && hit_b.dist <= hit_a.dist))
		{
			hit->dist = hit_b.dist;
			hit->normal = hit_b.normal;
			break ;
		}
		else if (hit_type_a == HIT_ENTER && hit_type_b == HIT_EXIT)
		{
			hit_a.min_dist = hit_a.dist + 1e-6;
			hit_a.dist = -INFINITY;
			object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_a);
			hit_type_a = classify_hit_type(object->csg_tree.left, &hit_a);
		}
		else if (hit_type_b == HIT_ENTER && hit_type_a == HIT_EXIT)
		{
			hit_b.min_dist = hit_b.dist + 1e-6;
			hit_b.dist = -INFINITY;
			object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_b);
			hit_type_b = classify_hit_type(object->csg_tree.right, &hit_b);
		}
		else
			break ;
	}
}

static void	hit_csg_inter(t_ray_object *object, t_ray_hit *hit)
{
	t_ray_hit	hit_a;
	t_ray_hit	hit_b;
	int			hit_type_a;
	int			hit_type_b;

	setup_csg_hit(&hit_a, object->csg_tree.left, hit);
	setup_csg_hit(&hit_b, object->csg_tree.right, hit);
	object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_a);
	object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_b);
	hit_type_a = classify_hit_type(object->csg_tree.left, &hit_a);
	hit_type_b = classify_hit_type(object->csg_tree.right, &hit_b);
	while (1)
	{
		if (hit_type_a == HIT_MISS || hit_type_b == HIT_MISS)
			break ;
		else if ((hit_type_a == HIT_ENTER && hit_type_b == HIT_EXIT && hit_a.dist <= hit_b.dist)
			|| (hit_type_a == HIT_EXIT && hit_type_b == HIT_EXIT && hit_a.dist <= hit_b.dist))
		{
			hit->dist = hit_a.dist;
			hit->normal = hit_a.normal;
			break ;
		}
		else if ((hit_type_b == HIT_ENTER && hit_type_a == HIT_EXIT && hit_b.dist <= hit_a.dist)
			|| (hit_type_b == HIT_EXIT && hit_type_a == HIT_EXIT && hit_b.dist <= hit_a.dist))
		{
			hit->dist = hit_b.dist;
			hit->normal = hit_b.normal;
			break ;
		}
		else if ((hit_type_a == HIT_EXIT && hit_type_b == HIT_ENTER)
			|| (hit_type_a == HIT_ENTER && hit_type_b == HIT_ENTER && hit_a.dist <= hit_b.dist))
		{
			hit_a.min_dist = hit_a.dist + 1e-6;
			hit_a.dist = -INFINITY;
			object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_a);
			hit_type_a = classify_hit_type(object->csg_tree.left, &hit_a);
		}
		else if ((hit_type_b == HIT_EXIT && hit_type_a == HIT_ENTER)
			|| (hit_type_b == HIT_ENTER && hit_type_a == HIT_ENTER && hit_b.dist <= hit_a.dist))
		{
			hit_b.min_dist = hit_b.dist + 1e-6;
			hit_b.dist = -INFINITY;
			object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_b);
			hit_type_b = classify_hit_type(object->csg_tree.right, &hit_b);
		}
		else
			break ;
	}
}

static void	hit_csg_sub(t_ray_object *object, t_ray_hit *hit)
{
	t_ray_hit	hit_a;
	t_ray_hit	hit_b;
	int			hit_type_a;
	int			hit_type_b;

	setup_csg_hit(&hit_a, object->csg_tree.left, hit);
	setup_csg_hit(&hit_b, object->csg_tree.right, hit);
	object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_a);
	object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_b);
	hit_type_a = classify_hit_type(object->csg_tree.left, &hit_a);
	hit_type_b = classify_hit_type(object->csg_tree.right, &hit_b);
	while (1)
	{
		if (hit_type_a == HIT_MISS)
			break ;
		else if (hit_type_b == HIT_MISS
			|| (hit_type_a == HIT_ENTER && hit_type_b == HIT_ENTER && hit_a.dist <= hit_b.dist)
			|| (hit_type_a == HIT_EXIT && hit_type_b == HIT_ENTER && hit_a.dist <= hit_b.dist))
		{
			hit->dist = hit_a.dist;
			hit->normal = hit_a.normal;
			break ;
		}
		else if ((hit_type_b == HIT_ENTER && hit_type_a == HIT_EXIT && hit_b.dist <= hit_a.dist)
			|| (hit_type_b == HIT_EXIT && hit_type_a == HIT_EXIT && hit_b.dist <= hit_a.dist))
		{
			hit->dist = hit_b.dist;
			if (hit_type_a == HIT_EXIT
				&& (hit_type_b == HIT_ENTER || hit_type_b == HIT_EXIT))
				hit_b.normal = vec3d_scalar(hit_b.normal, -1);
			hit->normal = hit_b.normal;
			break ;
		}
		else if ((hit_type_a == HIT_EXIT && hit_type_b == HIT_EXIT)
			|| (hit_type_a == HIT_ENTER && hit_type_b == HIT_EXIT && hit_a.dist <= hit_b.dist))
		{
			hit_a.min_dist = hit_a.dist + 1e-6;
			hit_a.dist = -INFINITY;
			object->csg_tree.left->hit_fn(object->csg_tree.left, &hit_a);
			hit_type_a = classify_hit_type(object->csg_tree.left, &hit_a);
		}
		else if ((hit_type_b == HIT_ENTER && hit_type_a == HIT_ENTER)
			|| (hit_type_b == HIT_EXIT && hit_type_a == HIT_ENTER && hit_b.dist <= hit_a.dist))
		{
			hit_b.min_dist = hit_b.dist + 1e-6;
			hit_b.dist = -INFINITY;
			object->csg_tree.right->hit_fn(object->csg_tree.right, &hit_b);
			hit_type_b = classify_hit_type(object->csg_tree.right, &hit_b);
		}
		else
			break ;
	}
}

void		hit_csg(t_ray_object *object, t_ray_hit *hit)
{
	if (object->type == RAYOBJ_CSGUNION)
		hit_csg_union(object, hit);
	else if (object->type == RAYOBJ_CSGINTER)
		hit_csg_inter(object, hit);
	else if (object->type == RAYOBJ_CSGSUB)
		hit_csg_sub(object, hit);
}
