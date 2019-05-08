/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 12:36:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "ray_object.h"
#include "math_utils.h"

static int		get_ray_light_type(t_json_token *token)
{
	if (token->type == JSON_STRING)
	{
		if (ft_strequ(token->value.str, "light"))
			return (RAYOBJ_LIGHT);
		else if (ft_strequ(token->value.str, "ambient_light"))
			return (RAYOBJ_AMBIENTLIGHT);
	}
	return (RAYOBJ_UNKNOWN);
}

int				get_ray_object_type(t_json_token *token)
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
		else if (ft_strequ(token->value.str, "tanglecube"))
			return (RAYOBJ_TANGLECUBE);
		else if (ft_strequ(token->value.str, "trianglemesh"))
			return (RAYOBJ_TRIANGLEMESH);
	}
	return (get_ray_light_type(token));
}

static void		parse_object_property_3(t_json_token *child
	, t_ray_object *object, t_error *err)
{
	if (ft_strequ(child->key, "perlin"))
	{
		object->perlin.enabled = 1;
		object->perlin.color = read_json_color(child, err);
	}
	else if (ft_strequ(child->key, "wood"))
	{
		object->wood.enabled = 1;
		object->wood.color = read_json_color(child, err);
	}
	else if (ft_strequ(child->key, "objfile_path"))
	{
		if (child->type != JSON_STRING
			|| ft_strlen(child->value.str) > PATH_MAX)
			*err = ERR_INVALIDSCENE;
		else
			ft_strcpy(object->objfile_path, child->value.str);
	}
	else
		parse_limits(child, object, err);
}

static void		parse_object_property_2(t_json_token *child
	, t_ray_object *object, t_error *err)
{
	if (ft_strequ(child->key, "specular"))
		object->specular = clamp(read_json_double(child, err), 0, 1);
	else if (ft_strequ(child->key, "shininess"))
		object->shininess = read_json_double(child, err);
	else if (ft_strequ(child->key, "reflective"))
		object->reflective = clamp(read_json_double(child, err), 0, 1);
	else if (ft_strequ(child->key, "refractive"))
		object->refractive = read_json_double(child, err);
	else if (ft_strequ(child->key, "refractive_factor"))
		object->rf_factor = clamp(read_json_double(child, err), 0, 1);
	else if (ft_strequ(child->key, "vertices"))
		*err = parse_ray_object_vertices(child, object->vertices);
	else if (ft_strequ(child->key, "checkerboard"))
		*err = parse_ray_object_checker(child, &object->checker);
	else if (ft_strequ(child->key, "bump"))
		object->bump = read_json_double(child, err);
	else if (ft_strequ(child->key, "wavy_effect"))
		object->wavy_effect = read_json_boolean(child, err);
	else if (ft_strequ(child->key, "roughness"))
		object->roughness = read_json_double(child, err);
	else
		parse_object_property_3(child, object, err);
}

void			parse_object_property(t_json_token *child
	, t_ray_object *object, t_error *err)
{
	*err = ERR_NOERROR;
	if (ft_strequ(child->key, "type"))
		object->type = get_ray_object_type(child);
	else if (ft_strequ(child->key, "origin"))
		object->origin = read_json_vec3d(child, err);
	else if (ft_strequ(child->key, "rotation"))
		object->rotation = parse_vec3d_rotation(child, err);
	else if (ft_strequ(child->key, "size"))
		object->size = read_json_vec3d(child, err);
	else if (ft_strequ(child->key, "color"))
		object->color = read_json_color(child, err);
	else if (ft_strequ(child->key, "scale"))
		object->scale = read_json_double(child, err);
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
	else
		parse_object_property_2(child, object, err);
}
