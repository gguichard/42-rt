/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_spatial_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:43:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/09 18:05:25 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

int		draw_objvalue_one(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 477;
	msg->pos.y = 77;
	if (!(msg->str = ft_sprintf("%.1lf", obj->rotation.x
					* (180.0 / M_PI))))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 565;
	msg->pos.y = 77;
	if (!(msg->str = ft_sprintf("%.1lf", obj->rotation.y
					* (180.0 / M_PI))))
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
	if (!(msg->str = ft_sprintf("%.1lf", obj->rotation.z
					* (180.0 / M_PI))))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 477;
	msg->pos.y = 45;
	if (!(msg->str = ft_sprintf("%.1lf", obj->origin.x)))
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
	if (!(msg->str = ft_sprintf("%.1lf", obj->origin.y)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 653;
	msg->pos.y = 45;
	if (!(msg->str = ft_sprintf("%.1lf", obj->origin.z)))
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
	set_rgba_text(&(msg.bg_color), 0xE1E1E1);
	set_rgba_text(&(msg.fg_color), 0x0);
	if (!(draw_objvalue_one(&(msg), data->current)))
		return (0);
	if (!(draw_objvalue_two(&(msg), data->current)))
		return (0);
	if (!(draw_objvalue_three(&(msg), data->current)))
		return (0);
	return (1);
}
