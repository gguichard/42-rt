/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/01 12:29:55 by roduquen         ###   ########.fr       */
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

static t_error	parse_ray_object(t_json_token *token, t_ray_object *object)
{
	t_error			err;
	t_json_token	*child;

	if (token->type != JSON_OBJECT)
		err = ERR_SCENEBADFORMAT;
	else
	{
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
			object->quat_rotate = xyz_rot_to_quat(vec3d_scalar(object->rotation
						, -1));
			object->quat_invert_rotate = quaternion_conj(object->quat_rotate);
			assign_object_functions(object);
		}
	}
	return (err);
}

static t_error	create_object_and_add_to_scene(t_data *data
		, t_json_token *child)
{
	t_error			err;
	t_ray_object	*obj;
	t_vector		*vector;

	if ((obj = ft_memalloc(sizeof(t_ray_object))) == NULL)
		err = ERR_UNEXPECTED;
	else
	{
		obj->diffuse = 1.0;
		err = parse_ray_object(child, obj);
		if (err == ERR_NOERROR)
		{
			vector = (obj->type == RAYOBJ_LIGHT
					|| obj->type == RAYOBJ_AMBIENTLIGHT)
				? &data->lights : &data->objects;
			if (!ft_vecpush(vector, obj))
				err = ERR_UNEXPECTED;
		}
		if (err != ERR_NOERROR)
			free(obj);
	}
	return (err);
}

t_error			parse_ray_objects(t_data *data, t_json_token *token)
{
	t_error			err;
	t_json_token	*child;

	if (token->type != JSON_ARRAY)
		return (ERR_SCENEBADFORMAT);
	err = ERR_NOERROR;
	child = token->value.child;
	while (err == ERR_NOERROR && child != NULL)
	{
		err = create_object_and_add_to_scene(data, child);
		child = child->next;
	}
	if (err != ERR_NOERROR)
	{
		ft_vecfree(&data->objects);
		ft_vecfree(&data->lights);
	}
	return (err);
}
