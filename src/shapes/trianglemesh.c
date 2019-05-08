/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trianglemesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:01:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 14:54:13 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "kd_tree.h"
#include "mesh_tree.h"
#include "ray_object.h"
#include "vec3d.h"

static double	hit_triangle_for_mesh(t_vec3d origin, t_vec3d direction
	, t_vec3d *vertices, double data[3])
{
	t_vec3d	tmp[5];
	double	inv_det;
	double	dist;

	tmp[0] = vec3d_sub(vertices[1], vertices[0]);
	tmp[1] = vec3d_sub(vertices[2], vertices[0]);
	tmp[2] = vec3d_cross(direction, tmp[1]);
	data[0] = vec3d_dot(tmp[0], tmp[2]);
	if (fabs(data[0]) < EPSILON)
		return (-INFINITY);
	inv_det = 1.0 / data[0];
	tmp[3] = vec3d_sub(origin, vertices[0]);
	data[1] = inv_det * vec3d_dot(tmp[3], tmp[2]);
	if (data[1] < 0.0 || data[1] > 1.0)
		return (-INFINITY);
	tmp[4] = vec3d_cross(tmp[3], tmp[0]);
	data[2] = inv_det * vec3d_dot(direction, tmp[4]);
	if (data[2] < 0.0 || data[1] + data[2] > 1.0)
		return (-INFINITY);
	dist = inv_det * vec3d_dot(tmp[1], tmp[4]);
	if (dist > EPSILON)
		return (dist);
	return (-INFINITY);
}

static t_vec3d	get_triangle_normal_for_mesh(double barycentric[2]
	, t_vec3d *normals)
{
	double	alpha;
	double	beta;
	double	gamma;
	t_vec3d	normal;

	alpha = barycentric[0];
	beta = barycentric[1];
	gamma = 1 - alpha - beta;
	normal = vec3d_scalar(normals[2], gamma);
	normal = vec3d_add(vec3d_scalar(normals[1], beta), normal);
	normal = vec3d_add(vec3d_scalar(normals[0], alpha), normal);
	return (vec3d_unit(normal));
}

static void		hit_triangle_in_mesh(t_kd_tree *tree, t_ray_hit *hit)
{
	size_t		idx;
	double		dist;
	t_triangle	*triangle;
	double		data[3];

	idx = 0;
	while (idx < tree->objects.size)
	{
		triangle = (t_triangle *)tree->objects.data[idx];
		dist = hit_triangle_for_mesh(hit->origin, hit->direction
				, triangle->vertices, data);
		if (dist > EPSILON
			&& (hit->dist == -INFINITY || dist < hit->dist))
		{
			hit->dist = dist;
			hit->normal = get_triangle_normal_for_mesh(data + 1
					, triangle->normals);
			if (data[0] < EPSILON)
				hit->normal = vec3d_scalar(hit->normal, -1);
		}
		idx++;
	}
}

static int		hit_trianglemesh_depth(t_kd_tree *tree, t_ray_hit *hit)
{
	if (tree != NULL && hit_boundingbox(tree->bbox_min, tree->bbox_max, hit))
	{
		if (tree->left != NULL || tree->right != NULL)
			return (hit_trianglemesh_depth(tree->left, hit)
				|| hit_trianglemesh_depth(tree->right, hit));
		else
			hit_triangle_in_mesh(tree, hit);
	}
	return (0);
}

void			hit_trianglemesh(t_ray_object *object, t_ray_hit *hit)
{
	hit_trianglemesh_depth(&object->mesh_tree, hit);
}
