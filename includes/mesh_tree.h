/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_tree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:14:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/04 23:17:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_TREE_H
# define MESH_TREE_H

# include "libft.h"
# include "vec3d.h"

typedef struct s_mesh_tree	t_mesh_tree;

typedef struct		s_triangle
{
	t_vec3d			vertices[3];
	t_vec3d			normals[3];
}					t_triangle;

struct				s_mesh_tree
{
	t_vec3d			bbox_min;
	t_vec3d			bbox_max;
	t_vector		triangles;
	t_mesh_tree		*left;
	t_mesh_tree		*right;
};

int					create_mesh_tree(t_mesh_tree *tree, char axis, int depth);

#endif
