/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_effect_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:11:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/10 18:40:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

int		draw_rough_bump(t_text *msg, t_data *data)
{
	msg->pos.x = 800;
	msg->pos.y = 108;
	msg->police = data->lib.panel.arial_black_9;
	if (!(msg->str = double_as_string(data->current->bump, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 800;
	msg->pos.y = 124;
	if (!(msg->str = double_as_string(data->current->roughness, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_checker(t_text *msg, t_data *data)
{
	msg->pos.x = 800;
	msg->pos.y = 36;
	msg->police = data->lib.panel.arial_black_11;
	if (!(data->current->checker.size))
	{
		msg->str = "off";
		if (!(write_text(msg)))
			return (0);
	}
	else
	{
		msg->pos.x = 780;
		msg->str = "on";
		if (!(write_text(msg)))
			return (0);
		if (!(draw_checker_color(data)))
			return (0);
	}
	return (1);
}

int		draw_wood(t_text *msg, t_data *data)
{
	msg->pos.x = 800;
	msg->pos.y = 64;
	msg->police = data->lib.panel.arial_black_11;
	if (!(data->current->wood.enabled))
	{
		msg->str = "off";
		if (!(write_text(msg)))
			return (0);
	}
	else
	{
		msg->pos.x = 780;
		msg->str = "on";
		if (!(write_text(msg)))
			return (0);
		if (!(draw_wood_color(data)))
			return (0);
	}
	return (1);
}

int		draw_perlin(t_text *msg, t_data *data)
{
	msg->pos.x = 800;
	msg->pos.y = 87;
	msg->police = data->lib.panel.arial_black_11;
	if (!(data->current->perlin.enabled))
	{
		msg->str = "off";
		if (!(write_text(msg)))
			return (0);
	}
	else
	{
		msg->pos.x = 780;
		msg->str = "on";
		if (!(write_text(msg)))
			return (0);
		if (!(draw_perlin_color(data)))
			return (0);
	}
	return (1);
}

int		draw_obj_effect(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	set_rgba_text(&(msg.bg_color), 0xEBEBEB);
	set_rgba_text(&(msg.fg_color), 0x0);
	if (!(draw_rough_bump(&(msg), data)))
		return (0);
	if (!(draw_wood(&(msg), data)))
		return (0);
	if (!(draw_perlin(&(msg), data)))
		return (0);
	if (!(draw_checker(&(msg), data)))
		return (0);
	return (1);
}
