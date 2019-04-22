/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 03:52:54 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 03:55:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "ray_object.h"

t_error			setup_camera_properties(t_data *data, t_json_token *token)
{
	t_error			err;
	t_json_token	*child;

	if (token->type != JSON_OBJECT)
		return (ERR_SCENEBADFORMAT);
	err = ERR_NOERROR;
	child = token->value.child;
	while (err == ERR_NOERROR && child != NULL)
	{
		if (ft_strequ(child->key, "origin"))
			data->camera.origin = read_json_vec3d(child, &err);
		else if (ft_strequ(child->key, "direction"))
			data->camera.direction = read_json_vec3d(child, &err);
		child = child->next;
	}
	return (err);
}

t_obj_rotation	parse_obj_rotation(t_json_token *token, t_error *err)
{
	t_obj_rotation	rot;
	t_json_token	*child;

	ft_memset(&rot, 0, sizeof(t_obj_rotation));
	if (token->type != JSON_OBJECT)
		*err = ERR_SCENEBADFORMAT;
	else
	{
		*err = ERR_NOERROR;
		child = token->value.child;
		while (*err == ERR_NOERROR && child != NULL)
		{
			if (ft_strequ(child->key, "vector"))
				rot.vector = read_json_vec3d(child, err);
			else if (ft_strequ(child->key, "angle"))
				rot.angle = read_json_double(child, err);
			child = child->next;
		}
	}
	return (rot);
}
