/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 01:12:15 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/09 16:00:30 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include "panel.h"
#include "raytracer.h"

char	*get_obj_type(int id)
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
	if (id == 8)
		return ("HYPERBOLOID");
	if (id == 9)
		return ("TANGLECUBE");
	if (id == 9)
		return ("TRIANGLEMESH");
	return ("UNKNOWN");
}

int		draw_obj_name(t_data *data)
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
