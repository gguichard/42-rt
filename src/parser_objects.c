/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 04:09:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json_parser.h"
#include "raytracer.h"
#include "parser.h"
#include "error.h"
#include "ray_object.h"

static int		get_ray_object_type(t_json_token *token)
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
		else if (ft_strequ(token->value.str, "light"))
			type = RAYOBJ_LIGHT;
		else if (ft_strequ(token->value.str, "ambient_light"))
			type = RAYOBJ_AMBIENTLIGHT;
	}
	return (type);
}

static t_ray_object	parse_ray_object(t_json_token *token, t_error *err)
{
	t_ray_object	obj;
	t_json_token	*child;

	ft_memset(&obj, 0, sizeof(t_ray_object));
	if (token->type != JSON_OBJECT)
		*err = ERR_SCENEBADFORMAT;
	else
	{
		child = token->value.child;
		while (child != NULL)
		{
			if (ft_strequ(child->key, "type"))
				obj.type = get_ray_object_type(child);
			else if (ft_strequ(child->key, "origin"))
				obj.origin = read_json_vec3d(child, err);
			else if (ft_strequ(child->key, "normal"))
				obj.normal = read_json_vec3d(child, err);
			else if (ft_strequ(child->key, "rotation"))
				obj.rotation = parse_obj_rotation(child, err);
			else if (ft_strequ(child->key, "color"))
				obj.color = read_json_color(child, err);
			else if (ft_strequ(child->key, "radius"))
				obj.radius = read_json_double(child, err);
			else if (ft_strequ(child->key, "intensity"))
				obj.intensity = read_json_double(child, err);
			else if (ft_strequ(child->key, "specular"))
				obj.specular = read_json_double(child, err);
			else if (ft_strequ(child->key, "shininess"))
				obj.shininess = read_json_double(child, err);
			child = child->next;
		}
		if (obj.type == RAYOBJ_UNKNOWN)
			*err = ERR_SCENEBADOBJECT;
	}
	return (obj);
}

t_error				parse_ray_objects(t_data *data, t_json_token *token)
{
	t_error			err;
	t_json_token	*child;
	t_ray_object	obj;
	t_list			*elem;

	if (token->type != JSON_ARRAY)
		return (ERR_SCENEBADFORMAT);
	err = ERR_NOERROR;
	child = token->value.child;
	while (err == ERR_NOERROR && child != NULL)
	{
		obj = parse_ray_object(child, &err);
		if (err == ERR_NOERROR
				&& (elem = ft_lstnew(&obj, sizeof(t_ray_object))) == NULL)
			err = ERR_UNEXPECTED;
		if (err == ERR_NOERROR)
		{
			if (obj.type == RAYOBJ_LIGHT || obj.type == RAYOBJ_AMBIENTLIGHT)
				ft_lstadd(&data->lights, elem);
			else
				ft_lstadd(&data->objects, elem);
		}
		child = child->next;
	}
	if (err != ERR_NOERROR)
	{
		ft_lstfree(&data->objects);
		ft_lstfree(&data->lights);
	}
	return (err);
}
