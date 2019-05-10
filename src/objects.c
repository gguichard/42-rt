/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:37:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/09 20:16:35 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ray_object.h"
#include "kd_tree.h"
#include "mesh_tree.h"
#include "wf_obj_parser.h"
#include "error.h"

void			del_ray_object_properties(t_ray_object *object)
{
	if (object->csg_tree.left != NULL)
	{
		del_ray_object_properties(object->csg_tree.left);
		ft_memdel((void **)&object->csg_tree.left);
	}
	if (object->csg_tree.right != NULL)
	{
		del_ray_object_properties(object->csg_tree.right);
		ft_memdel((void **)&object->csg_tree.right);
	}
}

void			del_ray_object(void *data)
{
	t_ray_object	*object;

	object = (t_ray_object *)data;
	if (object->type == RAYOBJ_TRIANGLEMESH)
		del_kd_tree(&object->mesh_tree);
	del_ray_object_properties(object);
	free(data);
}

static t_error	create_mesh_tree_from_obj(t_ray_object *object)
{
	t_error		err;
	t_wf_obj	wf_obj;

	ft_printf("Loading \"%s\" file...\n", object->objfile_path);
	err = parse_wf_obj_file(object->objfile_path, &wf_obj, object->scale);
	if (err == ERR_NOERROR)
	{
		err = create_triangle_mesh_root(&wf_obj, &object->mesh_tree);
		if (err == ERR_NOERROR && !build_mesh_tree(&object->mesh_tree, 'x', 0))
			err = ERR_UNEXPECTED;
		free_wf_obj(&wf_obj);
	}
	ft_printf("\"%s\" finished.\n", object->objfile_path);
	return (err);
}

t_error			create_meshes_from_objects(t_vector *objects)
{
	t_error			err;
	size_t			idx;
	t_ray_object	*obj;

	err = ERR_NOERROR;
	idx = 0;
	while (err == ERR_NOERROR && idx < objects->size)
	{
		obj = (t_ray_object *)objects->data[idx];
		if (obj->type == RAYOBJ_TRIANGLEMESH && obj->scale != 0)
			err = create_mesh_tree_from_obj(obj);
		idx++;
	}
	return (err);
}