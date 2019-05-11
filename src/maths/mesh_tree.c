/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:03:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:07:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "kd_tree.h"
#include "mesh_tree.h"
#include "vec3d.h"
#include "math_utils.h"
#include "wf_obj_parser.h"
#include "error.h"

static double	get_midpoint_vertices(t_vec3d *vertices, char axis)
{
	double	total;

	total = 0;
	if (axis == 'x')
		total += vertices[0].x + vertices[1].x + vertices[2].x;
	else if (axis == 'y')
		total += vertices[0].y + vertices[1].y + vertices[2].y;
	else if (axis == 'z')
		total += vertices[0].z + vertices[1].z + vertices[2].z;
	return (total / 3);
}

static double	get_midpoint_and_compute_bbox(t_kd_tree *tree, char axis)
{
	size_t	idx;
	double	midpoint;
	t_vec3d	*vertices;

	idx = 0;
	midpoint = 0;
	tree->bbox_min = vec3d(INFINITY, INFINITY, INFINITY);
	tree->bbox_max = vec3d(-INFINITY, -INFINITY, -INFINITY);
	while (idx < tree->objects.size)
	{
		vertices = ((t_triangle *)tree->objects.data[idx])->vertices;
		midpoint += get_midpoint_vertices(vertices, axis);
		grow_bbox(&tree->bbox_min, &tree->bbox_max, vertices);
		grow_bbox(&tree->bbox_min, &tree->bbox_max, vertices + 1);
		grow_bbox(&tree->bbox_min, &tree->bbox_max, vertices + 2);
		idx++;
	}
	return (midpoint / tree->objects.size);
}

static int		push_triangle_to_leaf(t_kd_tree **root, t_triangle *triangle)
{
	if (*root == NULL)
	{
		*root = ft_memalloc(sizeof(t_kd_tree));
		if (*root == NULL)
			return (0);
	}
	return (ft_vecpush(&(*root)->objects, triangle));
}

int				build_mesh_tree(t_kd_tree *tree, char axis, int depth)
{
	int			ret;
	size_t		idx;
	double		midpoint;
	double		triangle_midpoint;
	t_triangle	*triangle;

	ret = 1;
	if (tree != NULL)
	{
		idx = 0;
		midpoint = get_midpoint_and_compute_bbox(tree, axis);
		if (depth++ > 10)
			return (1);
		while (ret && idx < tree->objects.size)
		{
			triangle = (t_triangle *)tree->objects.data[idx];
			triangle_midpoint = get_midpoint_vertices(triangle->vertices, axis);
			ret = push_triangle_to_leaf((triangle_midpoint < midpoint
						? &tree->left : &tree->right), triangle);
			idx++;
		}
		ret = ret && build_mesh_tree(tree->left, get_next_axis(axis), depth);
		ret = ret && build_mesh_tree(tree->right, get_next_axis(axis), depth);
	}
	return (ret);
}

t_error			create_triangle_mesh_root(t_wf_obj *wf_obj, t_kd_tree *root)
{
	t_error		err;
	size_t		idx;
	t_triangle	*trgl;

	err = err_noerror;
	idx = 0;
	while (err == err_noerror && (idx + 3) <= wf_obj->vertices.size)
	{
		if ((trgl = (t_triangle *)malloc(sizeof(t_triangle))) == NULL)
			err = err_unexpected;
		else
		{
			trgl->vertices[0] = *((t_vec3d *)wf_obj->vertices.data[idx]);
			trgl->vertices[1] = *((t_vec3d *)wf_obj->vertices.data[idx + 1]);
			trgl->vertices[2] = *((t_vec3d *)wf_obj->vertices.data[idx + 2]);
			trgl->normals[0] = *((t_vec3d *)wf_obj->normals.data[idx]);
			trgl->normals[1] = *((t_vec3d *)wf_obj->normals.data[idx + 1]);
			trgl->normals[2] = *((t_vec3d *)wf_obj->normals.data[idx + 2]);
			if (!ft_vecpush(&root->objects, trgl)
				&& (err = err_unexpected) == err_unexpected)
				free(trgl);
			idx += 3;
		}
	}
	return (err);
}
