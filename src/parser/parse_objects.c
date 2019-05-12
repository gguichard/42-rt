/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:09:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "raytracer.h"
#include "ray_object.h"
#include "error.h"
#include "quaternion.h"

static t_error	parse_ray_object(t_json_token *token, t_ray_object *object)
{
	t_error			err;
	t_json_token	*child;

	err = err_noerror;
	child = token->value.child;
	while (err == err_noerror && child != NULL)
	{
		parse_object_property(child, object, &err);
		child = child->next;
	}
	if (err == err_noerror)
	{
		if (object->type == RAYOBJ_UNKNOWN)
			err = err_scenebadobject;
		else
		{
			object->rot_quat = xyz_rot_to_quat(vec3d_scalar(object->rotation
						, -1));
			object->inv_rot_quat = quaternion_conj(object->rot_quat);
			err = process_object_after_parsing(object);
		}
	}
	return (err);
}

t_ray_object	*create_ray_object(t_json_token *child, t_error *err)
{
	t_ray_object	*object;

	object = NULL;
	if (child->type != JSON_OBJECT)
		*err = err_scenebadformat;
	else if ((object = ft_memalloc(sizeof(t_ray_object))) == NULL)
		*err = err_unexpected;
	else
	{
		object->scale = 1.0;
		object->diffuse = 1.0;
		*err = parse_ray_object(child, object);
		if (*err != err_noerror)
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
		return (err_scenebadformat);
	err = err_noerror;
	child = token->value.child;
	while (err == err_noerror && child != NULL)
	{
		object = create_ray_object(child, &err);
		if (err == err_noerror && (!ft_vecpush((object->type == RAYOBJ_LIGHT
						|| object->type == RAYOBJ_AMBIENTLIGHT)
					? &data->lights : &data->objects, object)))
			err = err_unexpected;
		child = child->next;
	}
	if (err != err_noerror)
	{
		ft_vecdel(&data->objects, del_ray_object);
		ft_vecfree(&data->lights);
	}
	return (err);
}
