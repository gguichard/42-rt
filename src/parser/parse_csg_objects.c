/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 19:48:14 by roduquen         ###   ########.fr       */
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

static void		parse_object_property_2(t_json_token *child
	, t_ray_object *object, t_error *err)
{
	if (ft_strequ(child->key, "union"))
	{
		
		object->tree = create_node();
		object->tree->type = CSG_UNION;
		object->tree-> = parse_ray_object(child, object);
	}
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
