/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:41:07 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/03 06:26:43 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "panel.h"

void	draw_camera_titles(t_text *msg)
{
	set_rgba_text(&(msg->fg_color), 0xFF);
	set_rgba_text(&(msg->bg_color), 0x87837D00);	
	msg->pos.x = 60;
	msg->pos.y = 5;
	msg->pos.w = 80;
	msg->pos.h = 20;	
	msg->str = "CAMERA";
	write_text(msg);
	msg->pos.x = 15;
	msg->pos.y = 30;
	msg->pos.w = 60;
	msg->pos.h = 20;
	msg->str = "position";
	write_text(msg);
	msg->pos.x = 105;
	msg->pos.y = 30;
	msg->pos.w = 80;
	msg->pos.h = 20;
	msg->str = "orientation";
	write_text(msg);
}

void	draw_camera_pos_title(t_text *msg)
{
	msg->pos.x = 15;
	msg->pos.y = 65;
	msg->pos.w = 10;
	msg->pos.h = 20;	
	msg->str = "x";
	write_text(msg);
	msg->pos.x = 15;
	msg->pos.y = 90;
	msg->pos.w = 10;
	msg->pos.h = 20;	
	msg->str = "y";
	write_text(msg);
	msg->pos.x = 15;
	msg->pos.y = 115;
	msg->pos.w = 10;
	msg->pos.h = 20;	
	msg->str = "z";
	write_text(msg);
}

void	draw_camera_angle_title(t_text *msg)
{
	msg->pos.x = 95;
	msg->pos.y = 65;
	msg->pos.w = 10;
	msg->pos.h = 20;	
	msg->str = "x";
	write_text(msg);
	msg->pos.x = 95;
	msg->pos.y = 90;
	msg->pos.w = 10;
	msg->pos.h = 20;	
	msg->str = "y";
	write_text(msg);
	msg->pos.x = 95;
	msg->pos.y = 115;
	msg->pos.w = 10;
	msg->pos.h = 20;	
	msg->str = "z";
	write_text(msg);
}

void	draw_camera_menu(t_text *msg)
{
	draw_camera_titles(msg);
	draw_camera_pos_title(msg);
	draw_camera_angle_title(msg);
}
