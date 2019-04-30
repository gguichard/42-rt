/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:07:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/30 17:16:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "vec3d.h"

t_error	parse_ray_object_rotation(t_json_token *token, t_obj_rotation *rot)
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
			if (ft_strequ(child->key, "vector"))
				rot->vector = vec3d_unit(read_json_vec3d(child, &err));
			else if (ft_strequ(child->key, "angle"))
				rot->angle = read_json_double(child, &err) / 180. * M_PI;
			child = child->next;
		}
	}
	return (err);
}
