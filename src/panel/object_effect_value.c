/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_effect_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:11:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/08 06:36:53 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

void	draw_rough_bump(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 800;
	msg->pos.y = 108;
	msg->str = ft_sprintf("%.1lf", obj->bump);
	write_text(msg, 9);
	free(msg->str);
	msg->pos.x = 800;
	msg->pos.y = 124;
	msg->str = ft_sprintf("%.1lf", obj->roughness);
	write_text(msg, 9);
	free(msg->str);
}

void	draw_checker(t_text *msg, t_data *data)
{
	msg->pos.x = 800;
	msg->pos.y = 36;
	if (!(data->current->checker.size))
	{
		msg->str = "off";
		write_text(msg, 11);
	}
	else
	{
		msg->pos.x = 780;
		msg->str = "on";
		write_text(msg, 11);
		draw_checker_color(data);
	}
}

void	draw_wood(t_text *msg, t_data *data)
{
	msg->pos.x = 800;
	msg->pos.y = 64;
	if (!(data->current->wood.enabled))
	{
		msg->str = "off";
		write_text(msg, 11);
	}
	else
	{
		msg->pos.x = 780;
		msg->str = "on";
		write_text(msg, 11);
		draw_wood_color(data);
	}
}

void	draw_perlin(t_text *msg, t_data *data)
{
	msg->pos.x = 800;
	msg->pos.y = 87;
	if (!(data->current->perlin.enabled))
	{
		msg->str = "off";
		write_text(msg, 11);
	}
	else
	{
		msg->pos.x = 780;
		msg->str = "on";
		write_text(msg, 11);
		draw_perlin_color(data);
	}
}

void	draw_obj_effect(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	set_rgba_text(&(msg.bg_color), 0xE1E1E1);
	set_rgba_text(&(msg.fg_color), 0x0);
	draw_rough_bump(&(msg), data->current);
	draw_wood(&(msg), data);
	draw_perlin(&(msg), data);
	draw_checker(&(msg), data);
}
