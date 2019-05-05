/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:37:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/05 19:22:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_tree.h"
#include "ray_object.h"
#include "wf_obj_parser.h"
#include "error.h"

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
