/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kd_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:03:39 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/04 18:11:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "math_utils.h"

static char		get_next_axis(char axis)
{
	if (axis == 'x')
		return ('y');
	else if (axis == 'y')
		return ('z');
	else if (axis == 'z')
		return ('x');
	else
		return ('?');
}

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

static int		push_triangle_to_leaf(t_mesh_tree **root, t_triangle *triangle)
{
	if (*root == NULL)
	{
		if ((*root = ft_memalloc(sizeof(t_mesh_tree))) == NULL)
			return (0);
	}
	return (ft_vecpush(&(*root)->triangles, triangle));
}

static double	get_midpoint_and_compute_bbox(t_mesh_tree *tree, char axis)
{
	size_t	idx;
	double	midpoint;
	t_vec3d	*vertices;

	idx = 0;
	midpoint = 0;
	tree->bbox_min = (t_vec3d){INFINITY, INFINITY, INFINITY};
	tree->bbox_max = (t_vec3d){-INFINITY, -INFINITY, -INFINITY};
	while (idx < tree->triangles.size)
	{
		vertices = ((t_triangle *)tree->triangles.data[idx])->vertices;
		midpoint += get_midpoint_vertices(vertices, axis);
		grow_bbox(&tree->bbox_min, &tree->bbox_max, vertices);
		grow_bbox(&tree->bbox_min, &tree->bbox_max, vertices + 1);
		grow_bbox(&tree->bbox_min, &tree->bbox_max, vertices + 2);
		idx++;
	}
	return (midpoint / tree->triangles.size);
}

int				create_mesh_tree(t_mesh_tree *tree, char axis, int depth)
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
		while (ret && idx < tree->triangles.size)
		{
			triangle = (t_triangle *)tree->triangles.data[idx];
			triangle_midpoint = get_midpoint_vertices(triangle->vertices, axis);
			ret = push_triangle_to_leaf((triangle_midpoint < midpoint
						? &tree->left : &tree->right), triangle);
			idx++;
		}
		ret = ret && create_mesh_tree(tree->left, get_next_axis(axis), depth);
		ret = ret && create_mesh_tree(tree->right, get_next_axis(axis), depth);
	}
	return (ret);
}
