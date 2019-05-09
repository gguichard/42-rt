/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_spatial_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:43:46 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/09 14:29:23 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"
#include "raytracer.h"

void	draw_obj_rot_value(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 477;
	msg->pos.y = 77;
	msg->str = ft_sprintf("%.1lf", obj->rotation.x * (180.0 / M_PI));
	write_text(msg);
	free(msg->str);
	msg->pos.x = 565;
	msg->pos.y = 77;
	msg->str = ft_sprintf("%.1lf", obj->rotation.y * (180.0 / M_PI));
	write_text(msg);
	free(msg->str);
	msg->pos.x = 653;
	msg->pos.y = 77;
	msg->str = ft_sprintf("%.1lf", obj->rotation.z * (180.0 / M_PI));
	write_text(msg);
	free(msg->str);
}

void	draw_obj_pos_value(t_text *msg, t_ray_object *obj)
{
	msg->pos.x = 477;
	msg->pos.y = 45;
	msg->str = ft_sprintf("%.1lf", obj->origin.x);
	write_text(msg);
	free(msg->str);
	msg->pos.x = 565;
	msg->pos.y = 45;
	msg->str = ft_sprintf("%.1lf", obj->origin.y);
	write_text(msg);
	free(msg->str);
	msg->pos.x = 653;
	msg->pos.y = 45;
	msg->str = ft_sprintf("%.1lf", obj->origin.z);
	write_text(msg);
	free(msg->str);
}

void	draw_obj_spatial(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	msg.police = data->lib.panel.arial_black_11;
	set_rgba_text(&(msg.bg_color), 0xE1E1E1);
	set_rgba_text(&(msg.fg_color), 0x0);
	draw_obj_pos_value(&(msg), data->current);
	draw_obj_rot_value(&(msg), data->current);
}
