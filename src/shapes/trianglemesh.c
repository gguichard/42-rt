/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trianglemesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:01:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/04 06:40:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "math_utils.h"

static double	hit_triangle_for_mesh(t_vec3d origin, t_vec3d direction
		, t_vec3d *vertices)
{
	t_vec3d	tmp[5];
	double	var[4];

	tmp[0] = vec3d_sub(vertices[1], vertices[0]);
	tmp[1] = vec3d_sub(vertices[2], vertices[0]);
	tmp[2] = vec3d_cross(direction, tmp[1]);
	var[0] = vec3d_dot(tmp[0], tmp[2]);
	if (fabs(var[0]) < EPSILON)
		return (-INFINITY);
	var[1] = 1.0 / var[0];
	tmp[3] = vec3d_sub(origin, vertices[0]);
	var[2] = var[1] * vec3d_dot(tmp[3], tmp[2]);
	if (var[2] < 0.0 || var[2] > 1.0)
		return (-INFINITY);
	tmp[4] = vec3d_cross(tmp[3], tmp[0]);
	var[3] = var[1] * vec3d_dot(direction, tmp[4]);
	if (var[3] < 0.0 || var[2] + var[3] > 1.0)
		return (-INFINITY);
	return (var[1] * vec3d_dot(tmp[1], tmp[4]));
}

/*static double	hit_triangle_for_mesh(t_vec3d origin, t_vec3d direction
		, t_vec3d *vertices)
{
	t_vec3d	tmp[4];
	t_vec3d	normal;
	double	denom;
	double	ndot_ray_dir;
	double	dist;

	tmp[0] = vec3d_sub(vertices[1], vertices[0]);
	tmp[1] = vec3d_sub(vertices[2], vertices[0]);
	normal = vec3d_cross(tmp[0], tmp[1]);
	denom = vec3d_length2(normal);
	ndot_ray_dir = vec3d_dot(normal, direction);
	if (fabs(ndot_ray_dir) < EPSILON)
		return (-INFINITY);
	dist = (vec3d_dot(normal, origin) + vec3d_dot(normal, vertices[0])) / ndot_ray_dir;
	if (dist < 0)
		return (-INFINITY);
	return (dist);
	tmp[2] = vec3d_add(origin, vec3d_scalar(direction, dist));
	tmp[3] = vec3d_cross(vec3d_sub(vertices[1], vertices[0]), vec3d_sub(tmp[2], vertices[0]));
	if (vec3d_dot(normal, tmp[3]) < 0)
		return (-INFINITY);
	tmp[3] = vec3d_cross(vec3d_sub(vertices[2], vertices[1]), vec3d_sub(tmp[2], vertices[1]));
	if (vec3d_dot(normal, tmp[3]) < 0)
		return (-INFINITY);
	tmp[3] = vec3d_cross(vec3d_sub(vertices[0], vertices[2]), vec3d_sub(tmp[2], vertices[2]));
	if (vec3d_dot(normal, tmp[3]) < 0)
		return (-INFINITY);
	return (dist);
}*/

static int		hit_boundingbox(t_vec3d min, t_vec3d max, t_ray_hit *hit)
{
	double	xyz_min[3];
	double	xyz_max[3];

	xyz_min[0] = (min.x - hit->origin.x) / hit->direction.x;
	xyz_max[0] = (max.x - hit->origin.x) / hit->direction.x;
	if (xyz_min[0] > xyz_max[0])
		swap_f(&xyz_min[0], &xyz_max[0]);
	xyz_min[1] = (min.y - hit->origin.y) / hit->direction.y;
	xyz_max[1] = (max.y - hit->origin.y) / hit->direction.y;
	if (xyz_min[1] > xyz_max[1])
		swap_f(&xyz_min[1], &xyz_max[1]);
	if ((xyz_min[0] > xyz_max[1]) || (xyz_min[1] > xyz_max[0]))
		return (0);
	if (xyz_min[1] > xyz_min[0])
		xyz_min[0] = xyz_min[1];
	if (xyz_max[1] < xyz_max[0])
		xyz_max[0] = xyz_max[1];
	xyz_min[2] = (min.z - hit->origin.z) / hit->direction.z;
	xyz_max[2] = (max.z - hit->origin.z) / hit->direction.z;
	if (xyz_min[2] > xyz_max[2])
		swap_f(&xyz_min[2], &xyz_max[2]);
	return (!(xyz_min[0] > xyz_max[2] || xyz_min[2] > xyz_max[0]));
}

static t_vec3d	get_triangle_normal(t_vec3d origin, t_vec3d direction
		, t_vec3d *vertices, t_vec3d *normals)
{
	t_vec3d	tmp[5];
	double	var[4];
	t_vec3d	normal;

	tmp[0] = vec3d_sub(vertices[1], vertices[0]);
	tmp[1] = vec3d_sub(vertices[2], vertices[0]);
	tmp[2] = vec3d_cross(direction, tmp[1]);
	var[0] = vec3d_dot(tmp[0], tmp[2]);
	var[1] = 1.0 / var[0];
	tmp[3] = vec3d_sub(origin, vertices[0]);
	var[2] = var[1] * vec3d_dot(tmp[3], tmp[2]);
	tmp[4] = vec3d_cross(tmp[3], tmp[0]);
	var[3] = var[1] * vec3d_dot(direction, tmp[4]);
	normal = vec3d_add(vec3d_scalar(normals[0], var[2]), vec3d_add(vec3d_scalar(normals[1], var[3]), vec3d_scalar(normals[2], 1 - var[2] - var[3])));
	return (vec3d_unit(normal));
}

static int		hit_trianglemesh_depth(t_mesh_tree *tree, t_ray_hit *hit)
{
	size_t	idx;
	double	min_dist;
	double	dist;
	t_vec3d	normal;

	if (tree != NULL && hit_boundingbox(tree->bbox_min, tree->bbox_max, hit))
	{
		if (tree->left != NULL || tree->right != NULL)
			return (hit_trianglemesh_depth(tree->left, hit) || hit_trianglemesh_depth(tree->right, hit));
		else
		{
			idx = 0;
			min_dist = INFINITY;
			while (idx < tree->triangles.size)
			{
				dist = hit_triangle_for_mesh(hit->origin, hit->direction, ((t_triangle *)tree->triangles.data[idx])->vertices);
				if (dist > EPSILON && dist < min_dist)
				{
					normal = get_triangle_normal(hit->origin, hit->direction, ((t_triangle *)tree->triangles.data[idx])->vertices, ((t_triangle *)tree->triangles.data[idx])->normals);
					min_dist = dist;
				}
				idx++;
			}
			if (min_dist != INFINITY)
			{
				hit->dist = min_dist;
				hit->normal = normal;
				return (1);
			}
		}
	}
	return (0);
}

void			hit_trianglemesh(t_ray_object *object, t_ray_hit *hit)
{
	hit_trianglemesh_depth(&object->mesh_tree, hit);
	hit->inside = 0;
}
