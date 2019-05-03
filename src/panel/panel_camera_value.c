/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_camera_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:27:43 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/03 09:58:38 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"

void	draw_camera_pos_value(t_text *msg, t_camera *cam)
{
	msg->pos.x = 35;
	msg->pos.y = 65;
	msg->pos.w = 40;
	msg->pos.h = 20;	
	msg->str = ft_sprintf("%.2lf", cam->origin.x);
	write_text(msg);
	msg->pos.x = 35;
	msg->pos.y = 90;
	msg->pos.w = 40;
	msg->pos.h = 20;	
	msg->str = ft_sprintf("%.2lf", cam->origin.y);
	write_text(msg);
	msg->pos.x = 35;
	msg->pos.y = 115;
	msg->pos.w = 40;
	msg->pos.h = 20;	
	msg->str = ft_sprintf("%.2lf", cam->origin.z);
	write_text(msg);
}

void	draw_camera_angle_value(t_text *msg)
{
	msg->pos.x = 125;
	msg->pos.y = 65;
	msg->pos.w = 40;
	msg->pos.h = 20;	
	msg->str = "0.00 deg";
	write_text(msg);
	msg->pos.x = 125;
	msg->pos.y = 90;
	msg->pos.w = 40;
	msg->pos.h = 20;	
	msg->str = "0.00 deg";
	write_text(msg);
	msg->pos.x = 125;
	msg->pos.y = 115;
	msg->pos.w = 40;
	msg->pos.h = 20;	
	msg->str = "0.00 deg";
	write_text(msg);
}

void	draw_camera_value(t_text *msg, t_camera *cam)
{
	set_rgba_text(&(msg->bg_color),0xFFFFFF);
	set_rgba_text(&(msg->fg_color),0x0);
	draw_camera_pos_value(msg, cam);
	draw_camera_angle_value(msg);
}
