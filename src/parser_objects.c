/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 23:11:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json_parser.h"
#include "raytracer.h"
#include "parser.h"
#include "error.h"
#include "ray_object.h"

static int			get_ray_object_type(t_json_token *token)
{
	int	type;

	type = RAYOBJ_UNKNOWN;
	if (token->type == JSON_STRING)
	{
		if (ft_strequ(token->value.str, "sphere"))
			type = RAYOBJ_SPHERE;
		else if (ft_strequ(token->value.str, "plane"))
			type = RAYOBJ_PLANE;
		else if (ft_strequ(token->value.str, "cylinder"))
			type = RAYOBJ_CYLINDER;
		else if (ft_strequ(token->value.str, "cone"))
			type = RAYOBJ_CONE;
		else if (ft_strequ(token->value.str, "torus"))
			type = RAYOBJ_TORUS;
		else if (ft_strequ(token->value.str, "light"))
			type = RAYOBJ_LIGHT;
		else if (ft_strequ(token->value.str, "ambient_light"))
			type = RAYOBJ_AMBIENTLIGHT;
	}
	return (type);
}

static t_error		parse_object_property(t_json_token *child
		, t_ray_object *object)
{
	t_error	err;

	err = ERR_NOERROR;
	if (ft_strequ(child->key, "type"))
		object->type = get_ray_object_type(child);
	else if (ft_strequ(child->key, "origin"))
		object->origin = read_json_vec3d(child, &err);
	else if (ft_strequ(child->key, "rotation"))
		object->rotation = parse_ray_object_rotation(child, &err);
	else if (ft_strequ(child->key, "color"))
		object->color = read_json_color(child, &err);
	else if (ft_strequ(child->key, "radius"))
		object->radius = read_json_double(child, &err);
	else if (ft_strequ(child->key, "big_radius"))
		object->big_radius = read_json_double(child, &err);
	else if (ft_strequ(child->key, "intensity"))
		object->intensity = read_json_double(child, &err);
	else if (ft_strequ(child->key, "specular"))
		object->specular = read_json_double(child, &err);
	else if (ft_strequ(child->key, "shininess"))
		object->shininess = read_json_double(child, &err);
	return (err);
}

static t_error		parse_ray_object(t_json_token *token, t_ray_object *object)
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
			err = parse_object_property(child, object);
			child = child->next;
		}
		if (object->type == RAYOBJ_UNKNOWN)
			err = ERR_SCENEBADOBJECT;
	}
	return (err);
}

static t_error		create_object_and_add_to_scene(t_data *data
		, t_json_token *child)
{
	t_error			err;
	t_ray_object	obj;
	t_list			*elem;

	ft_memset(&obj, 0, sizeof(t_ray_object));
	err = parse_ray_object(child, &obj);
	if (err == ERR_NOERROR
			&& (elem = ft_lstnew(&obj, sizeof(t_ray_object))) == NULL)
		err = ERR_UNEXPECTED;
	if (err == ERR_NOERROR)
		ft_lstadd((obj.type == RAYOBJ_LIGHT
					|| obj.type == RAYOBJ_AMBIENTLIGHT
					? &data->lights : &data->objects), elem);
	return (err);
}

t_error				parse_ray_objects(t_data *data, t_json_token *token)
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
		ft_lstfree(&data->objects);
		ft_lstfree(&data->lights);
	}
	return (err);
}
