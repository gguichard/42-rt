/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_light_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 06:41:00 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/08 06:37:41 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

void	draw_obj_phong_value(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 947;
	msg->pos.y = 28;
	msg->str = ft_sprintf("%.2lf", obj->diffuse);
	write_text(msg, 11);
	free(msg->str);
	msg->pos.x = 947;
	msg->pos.y = 45;
	msg->str = ft_sprintf("%.2lf", obj->specular);
	write_text(msg, 11);
	free(msg->str);
	msg->pos.x = 947;
	msg->pos.y = 64;
	msg->str = ft_sprintf("%.2lf", obj->shininess);
	write_text(msg, 11);
	free(msg->str);
}

void	draw_obj_light_value(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 947;
	msg->pos.y = 83;
	msg->str = ft_sprintf("%.2lf", obj->refractive);
	write_text(msg, 11);
	free(msg->str);
	msg->pos.x = 947;
	msg->pos.y = 102;
	msg->str = ft_sprintf("%.2lf", obj->reflective);
	write_text(msg, 11);
	free(msg->str);
	msg->pos.x = 947;
	msg->pos.y = 121;
	msg->str = ft_sprintf("%.2lf", obj->rf_factor);
	write_text(msg, 11);
	free(msg->str);
}

void	draw_obj_light(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	set_rgba_text(&(msg.bg_color), 0xE1E1E1);
	set_rgba_text(&(msg.fg_color), 0x0);
	draw_obj_phong_value(&(msg), data->current);
	draw_obj_light_value(&(msg), data->current);
}
