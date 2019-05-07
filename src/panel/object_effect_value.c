/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_effect_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:11:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/07 08:53:46 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

void	draw_obj_att1(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 800;
	msg->pos.y = 88;
	msg->str = ft_sprintf("%.1lf", obj->bump);
	write_text(msg, 11);
	free(msg->str);
	msg->pos.x = 800;
	msg->pos.y = 105;
	msg->str = ft_sprintf("%.1lf", obj->roughness);
	write_text(msg, 11);
	free(msg->str);
}

void	draw_obj_att2(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 800;
	msg->pos.y = 31;
	if (!(obj->wood.enabled))
		msg->str = "off";
	else	
		msg->str = "on";
	write_text(msg, 11);
	msg->pos.x = 800;
	msg->pos.y = 50;
	if (!(obj->checker.size))
		msg->str = "off";
	else	
		msg->str = "on";
	write_text(msg, 11);
	msg->pos.x = 800;
	msg->pos.y = 69;
	if (!(obj->perlin.enabled))
		msg->str = "off";
	else	
		msg->str = "on";
	write_text(msg, 11);
}

void	draw_obj_effect(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	set_rgba_text(&(msg.bg_color),0xE1E1E1);
	set_rgba_text(&(msg.fg_color),0x0);
	draw_obj_att1(&(msg), data->current);
	draw_obj_att2(&(msg), data->current);
}
