/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_camera_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:27:43 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/03 07:47:11 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "panel.h"

void	draw_camera_pos_value(t_text *msg)
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

void	draw_camera_angle_value(t_text *msg)
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

void	draw_camera_value(t_text *msg)
{
	draw_camera_pos_value(msg);
	draw_camera_angle_value(msg);
}
