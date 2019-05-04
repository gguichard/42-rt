/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trianglemesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:01:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/04 22:45:00 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "math_utils.h"

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

static int		hit_trianglemesh_depth(t_mesh_tree *tree, t_ray_hit *hit)
{
	size_t		idx;
	double		dist;
	t_triangle	*triangle;
	double		data[3];

	if (tree != NULL && hit_boundingbox(tree->bbox_min, tree->bbox_max, hit))
	{
		if (tree->left != NULL || tree->right != NULL)
			return (hit_trianglemesh_depth(tree->left, hit)
				|| hit_trianglemesh_depth(tree->right, hit));
		else
		{
			idx = 0;
			while (idx < tree->triangles.size)
			{
				triangle = (t_triangle *)tree->triangles.data[idx];
				dist = hit_triangle_for_mesh(hit->origin, hit->direction
						, triangle->vertices, data);
				if (dist > EPSILON
					&& (hit->dist == -INFINITY || dist < hit->dist))
				{
					hit->dist = dist;
					hit->normal = get_triangle_normal_for_mesh(data + 1
						, triangle->normals);
					hit->inside = (data[0] < EPSILON);
				}
				idx++;
			}
		}
	}
	return (0);
}

void			hit_trianglemesh(t_ray_object *object, t_ray_hit *hit)
{
	hit_trianglemesh_depth(&object->mesh_tree, hit);
}
