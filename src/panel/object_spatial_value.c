/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_spatial_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:43:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/10 18:45:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

int		draw_objvalue_one(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 477;
	msg->pos.y = 77;
	if (!(msg->str = double_as_string(obj->rotation.x * (180.0 / M_PI), 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 565;
	msg->pos.y = 77;
	if (!(msg->str = double_as_string(obj->rotation.y * (180.0 / M_PI), 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_objvalue_two(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 653;
	msg->pos.y = 77;
	if (!(msg->str = double_as_string(obj->rotation.z * (180.0 / M_PI), 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 477;
	msg->pos.y = 45;
	if (!(msg->str = double_as_string(obj->origin.x, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_objvalue_three(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 565;
	msg->pos.y = 45;
	if (!(msg->str = double_as_string(obj->origin.y, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 653;
	msg->pos.y = 45;
	if (!(msg->str = double_as_string(obj->origin.z, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_obj_spatial(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	msg.police = data->lib.panel.arial_black_11;
	set_rgba_text(&(msg.bg_color), 0xEBEBEB);
	set_rgba_text(&(msg.fg_color), 0x0);
	if (!(draw_objvalue_one(&(msg), data->current)))
		return (0);
	if (!(draw_objvalue_two(&(msg), data->current)))
		return (0);
	if (!(draw_objvalue_three(&(msg), data->current)))
		return (0);
	return (1);
}
