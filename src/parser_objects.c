/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/28 03:28:19 by gguichar         ###   ########.fr       */
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
#include "utils.h"

static int		get_ray_object_type(t_json_token *token)
{
	if (token->type == JSON_STRING)
	{
		if (ft_strequ(token->value.str, "sphere"))
			return (RAYOBJ_SPHERE);
		else if (ft_strequ(token->value.str, "plane"))
			return (RAYOBJ_PLANE);
		else if (ft_strequ(token->value.str, "cylinder"))
			return (RAYOBJ_CYLINDER);
		else if (ft_strequ(token->value.str, "cone"))
			return (RAYOBJ_CONE);
		else if (ft_strequ(token->value.str, "torus"))
			return (RAYOBJ_TORUS);
		else if (ft_strequ(token->value.str, "triangle"))
			return (RAYOBJ_TRIANGLE);
		else if (ft_strequ(token->value.str, "ellipsoid"))
			return (RAYOBJ_ELLIPSOID);
		else if (ft_strequ(token->value.str, "hyperboloid"))
			return (RAYOBJ_HYPERBOLOID);
		else if (ft_strequ(token->value.str, "light"))
			return (RAYOBJ_LIGHT);
		else if (ft_strequ(token->value.str, "ambient_light"))
			return (RAYOBJ_AMBIENTLIGHT);
	}
	return (RAYOBJ_UNKNOWN);
}

static void		parse_object_property(t_json_token *child
		, t_ray_object *object, t_error *err)
{
	*err = ERR_NOERROR;
	if (ft_strequ(child->key, "type"))
		object->type = get_ray_object_type(child);
	else if (ft_strequ(child->key, "origin"))
		object->origin = read_json_vec3d(child, err);
	else if (ft_strequ(child->key, "size"))
		object->size = read_json_vec3d(child, err);
	else if (ft_strequ(child->key, "color"))
		object->color = read_json_color(child, err);
	else if (ft_strequ(child->key, "angle"))
		object->angle = read_json_double(child, err) / 180 * M_PI;
	else if (ft_strequ(child->key, "radius"))
		object->radius = read_json_double(child, err);
	else if (ft_strequ(child->key, "big_radius"))
		object->big_radius = read_json_double(child, err);
	else if (ft_strequ(child->key, "intensity"))
		object->intensity = read_json_double(child, err);
	else if (ft_strequ(child->key, "diffuse"))
		object->diffuse = clamp(read_json_double(child, err), 0, 1);
	else if (ft_strequ(child->key, "specular"))
		object->specular = clamp(read_json_double(child, err), 0, 1);
	else if (ft_strequ(child->key, "shininess"))
		object->shininess = read_json_double(child, err);
	else if (ft_strequ(child->key, "reflective"))
		object->reflective = clamp(read_json_double(child, err), 0, 1);
	else if (ft_strequ(child->key, "refractive"))
		object->refractive = read_json_double(child, err);
	else if (ft_strequ(child->key, "refractive_factor"))
		object->rf_factor = clamp(read_json_double(child, err), 0, 1);
	else if (ft_strequ(child->key, "rotation"))
		*err = parse_ray_object_rotation(child, &object->rotation);
	else if (ft_strequ(child->key, "vertices"))
		*err = parse_ray_object_vertices(child, object->vertices);
	else if (ft_strequ(child->key, "bump"))
		object->bump = read_json_double(child, err);
	else if (ft_strequ(child->key, "normal_circle"))
		object->normal_circle = read_json_double(child, err);
	else if (ft_strequ(child->key, "checkerboard"))
	{
		object->checkerboard.color = read_json_color(child, err);
		object->checkerboard.on = 1;
	}
	else if (ft_strequ(child->key, "roughness"))
		object->roughness = read_json_double(child, err);
}

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
			assign_object_functions(object);
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
