/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vertices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:11:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/30 17:12:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "vec3d.h"

t_error	parse_ray_object_vertices(t_json_token *token, t_vec3d *vertices)
{
	t_error			err;
	t_json_token	*child;
	int				idx;

	if (token->type != JSON_ARRAY)
		err = ERR_NOERROR;
	else
	{
		err = ERR_NOERROR;
		child = token->value.child;
		idx = 0;
		while (err == ERR_NOERROR && child != NULL && idx < 3)
		{
			vertices[idx] = read_json_vec3d(child, &err);
			child = child->next;
			idx++;
		}
		if (idx != 3 || child != NULL)
			err = ERR_SCENEBADFORMAT;
	}
	return (err);
}
