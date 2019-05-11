/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:07:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:07:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "vec3d.h"

t_vec3d	parse_vec3d_rotation(t_json_token *token, t_error *err)
{
	t_vec3d			rot;

	rot = read_json_vec3d(token, err);
	if (*err == err_noerror)
	{
		rot.x = rot.x / 180. * M_PI;
		rot.y = rot.y / 180. * M_PI;
		rot.z = rot.z / 180. * M_PI;
	}
	return (rot);
}
