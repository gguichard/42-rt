/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 01:12:15 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/11 15:47:31 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "panel.h"
#include "raytracer.h"

static char		*get_obj_type1(int id)
{
	if (id == 1)
		return ("SPHERE");
	if (id == 2)
		return ("PLANE");
	if (id == 3)
		return ("CYLINDER");
	if (id == 4)
		return ("CONE");
	if (id == 5)
		return ("TORUS");
	if (id == 6)
		return ("TRIANGLE");
	if (id == 7)
		return ("ELLIPSOID");
	return (NULL);
}

static char		*get_obj_type2(int id)
{
	if (id == 8)
		return ("HYPERBOLOID");
	if (id == 9)
		return ("TANGLECUBE");
	if (id == 10)
		return ("TRIANGLEMESH");
	if (id == 11)
		return ("CSG UNION");
	if (id == 12)
		return ("CSG SUB");
	if (id == 13)
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
