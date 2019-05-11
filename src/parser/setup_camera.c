/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:05:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:09:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "raytracer.h"
#include "error.h"
#include "vec3d.h"
#include "math_utils.h"

t_error	setup_camera_properties(t_data *data, t_json_token *token)
{
	t_error			err;
	t_json_token	*child;

	if (token->type != JSON_OBJECT)
		return (err_scenebadformat);
	err = err_noerror;
	child = token->value.child;
	while (err == err_noerror && child != NULL)
	{
		if (ft_strequ(child->key, "origin"))
			data->camera.origin = read_json_vec3d(child, &err);
		else if (ft_strequ(child->key, "rotation"))
			data->camera.rotation = parse_vec3d_rotation(child, &err);
		else if (ft_strequ(child->key, "fov"))
			data->camera.fov = tan(clamp(read_json_double(child, &err), 40, 120)
					* .5 / 180 * M_PI);
		child = child->next;
	}
	return (err);
}
