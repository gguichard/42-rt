/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_tree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:14:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/05 05:42:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_TREE_H
# define MESH_TREE_H

# include "libft.h"
# include "kd_tree.h"
# include "vec3d.h"
# include "error.h"
# include "wf_obj_parser.h"

typedef struct		s_triangle
{
	t_vec3d			vertices[3];
	t_vec3d			normals[3];
}					t_triangle;

t_error				create_meshes_from_objects(t_vector *objects);
t_error				create_triangle_mesh_root(t_wf_obj *wf_obj
	, t_kd_tree *root);
int					build_mesh_tree(t_kd_tree *tree, char axis, int depth);

#endif
