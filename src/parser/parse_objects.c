/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 23:26:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "json_parser.h"
#include "raytracer.h"
#include "parser.h"
#include "error.h"
#include "ray_object.h"
#include "math_utils.h"
#include "quaternion.h"

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

static void		del_ray_object(void *ptr)
{
	t_ray_object	*object;

	object = (t_ray_object *)ptr;
	del_ray_object_properties(object);
	free(ptr);
}

static t_error	parse_ray_object(t_json_token *token, t_ray_object *object)
{
	t_error			err;
	t_json_token	*child;

	err = ERR_NOERROR;
	child = token->value.child;
	while (err == ERR_NOERROR && child != NULL)
	{
		parse_object_property(child, object, &err);
		child = child->next;
	}
	if (object->type == RAYOBJ_UNKNOWN)
		err = ERR_SCENEBADOBJECT;
	else
	{
		object->rot_quat = xyz_rot_to_quat(vec3d_scalar(object->rotation, -1));
		object->inv_rot_quat = quaternion_conj(object->rot_quat);
		err = process_object_after_parsing(object);
	}
	return (err);
}

t_ray_object	*create_ray_object(t_json_token *child, t_error *err)
{
	t_ray_object	*object;

	object = NULL;
	if (child->type != JSON_OBJECT)
		*err = ERR_SCENEBADFORMAT;
	else if ((object = ft_memalloc(sizeof(t_ray_object))) == NULL)
		*err = ERR_UNEXPECTED;
	else
	{
		object->scale = 1.0;
		object->diffuse = 1.0;
		*err = parse_ray_object(child, object);
		if (*err != ERR_NOERROR)
		{
			del_ray_object_properties(object);
			ft_memdel((void **)&object);
		}
	}
	return (object);
}

t_error			parse_ray_objects(t_data *data, t_json_token *token)
{
	t_error			err;
	t_json_token	*child;
	t_ray_object	*object;

	if (token->type != JSON_ARRAY)
		return (ERR_SCENEBADFORMAT);
	err = ERR_NOERROR;
	child = token->value.child;
	while (err == ERR_NOERROR && child != NULL)
	{
		object = create_ray_object(child, &err);
		if (err == ERR_NOERROR && (!ft_vecpush((object->type == RAYOBJ_LIGHT
						|| object->type == RAYOBJ_AMBIENTLIGHT)
					? &data->lights : &data->objects, object)))
				err = ERR_UNEXPECTED;
		child = child->next;
	}
	if (err != ERR_NOERROR)
	{
		ft_vecdel(&data->objects, del_ray_object);
		ft_vecfree(&data->lights);
	}
	return (err);
}
