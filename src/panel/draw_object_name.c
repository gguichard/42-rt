/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 01:12:15 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/12 02:28:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "panel.h"
#include "raytracer.h"

static char		*get_obj_type1(int id)
{
	if (id == RAYOBJ_SPHERE)
		return ("SPHERE");
	if (id == RAYOBJ_PLANE)
		return ("PLANE");
	if (id == RAYOBJ_CYLINDER)
		return ("CYLINDER");
	if (id == RAYOBJ_CONE)
		return ("CONE");
	if (id == RAYOBJ_TORUS)
		return ("TORUS");
	if (id == RAYOBJ_TRIANGLE)
		return ("TRIANGLE");
	if (id == RAYOBJ_ELLIPSOID)
		return ("ELLIPSOID");
	return (NULL);
}

static char		*get_obj_type2(int id)
{
	if (id == RAYOBJ_HYPERBOLOID)
		return ("HYPERBOLOID");
	if (id == RAYOBJ_TANGLECUBE)
		return ("TANGLECUBE");
	if (id == RAYOBJ_TRIANGLEMESH)
		return ("MESH");
	if (id == RAYOBJ_CSGUNION)
		return ("CSG UNION");
	if (id == RAYOBJ_CSGSUB)
		return ("CSG SUB");
	if (id == RAYOBJ_CSGINTER)
		return ("CSG INTER");
	return (NULL);
}

char			*get_obj_type(int id)
{
	char	*str;

	str = NULL;
	str = get_obj_type1(id);
	if (!str)
		str = get_obj_type2(id);
	if (!str)
		return ("UNKNOWN");
	return (str);
}

int				draw_obj_name(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	set_rgba_text(&(msg.bg_color), 0xA6A6A6);
	set_rgba_text(&(msg.fg_color), 0xFF0000);
	msg.pos.x = 490;
	msg.pos.y = 12;
	msg.str = get_obj_type(data->current->type);
	msg.police = data->lib.panel.arial_black_13;
	if (!(write_text(&(msg))))
		return (0);
	return (1);
}
