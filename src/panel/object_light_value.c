/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_light_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 06:41:00 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/09 18:05:03 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

int		draw_objlight_one(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 947;
	msg->pos.y = 28;
	if (!(msg->str = ft_sprintf("%.2lf", obj->diffuse)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 947;
	msg->pos.y = 45;
	if (!(msg->str = ft_sprintf("%.2lf", obj->specular)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_objlight_two(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 947;
	msg->pos.y = 64;
	if (!(msg->str = ft_sprintf("%.2lf", obj->shininess)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 947;
	msg->pos.y = 83;
	if (!(msg->str = ft_sprintf("%.2lf", obj->refractive)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_objlight_three(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 947;
	msg->pos.y = 102;
	if (!(msg->str = ft_sprintf("%.2lf", obj->reflective)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 947;
	msg->pos.y = 121;
	if (!(msg->str = ft_sprintf("%.2lf", obj->rf_factor)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_obj_light(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	msg.police = data->lib.panel.arial_black_11;
	set_rgba_text(&(msg.bg_color), 0xE1E1E1);
	set_rgba_text(&(msg.fg_color), 0x0);
	if (!(draw_objlight_one(&(msg), data->current)))
		return (0);
	if (!(draw_objlight_two(&(msg), data->current)))
		return (0);
	if (!(draw_objlight_three(&(msg), data->current)))
		return (0);
	return (1);
}
