/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 01:06:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "ray_object.h"
#include "math_utils.h"

static void	parse_limits_2(t_json_token *child, t_ray_object *object
	, t_error *err)
{
	if (ft_strequ(child->key, "y_min"))
	{
		object->cut_plane.on_ymin = 1;
		object->cut_plane.min.y = read_json_double(child, err);
	}
	else if (ft_strequ(child->key, "z_min"))
	{
		object->cut_plane.on_zmin = 1;
		object->cut_plane.min.z = read_json_double(child, err);
	}
}

void		parse_limits(t_json_token *child, t_ray_object *object
	, t_error *err)
{
	if (ft_strequ(child->key, "x_max"))
	{
		object->cut_plane.on_xmax = 1;
		object->cut_plane.max.x = read_json_double(child, err);
	}
	else if (ft_strequ(child->key, "y_max"))
	{
		object->cut_plane.on_ymax = 1;
		object->cut_plane.max.y = read_json_double(child, err);
	}
	else if (ft_strequ(child->key, "z_max"))
	{
		object->cut_plane.on_zmax = 1;
		object->cut_plane.max.z = read_json_double(child, err);
	}
	else if (ft_strequ(child->key, "x_min"))
	{
		object->cut_plane.on_xmin = 1;
		object->cut_plane.min.x = read_json_double(child, err);
	}
	else
		parse_limits_2(child, object, err);
}
