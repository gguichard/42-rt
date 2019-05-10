/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_camera_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:27:43 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/10 18:45:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "panel.h"
#include "vec3d.h"

int		draw_camvalue_one(t_text *msg, t_camera *cam)
{
	msg->pos.x = 125;
	msg->pos.y = 65;
	if (!(msg->str = double_as_string(cam->origin.x, 2)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 125;
	msg->pos.y = 87;
	if (!(msg->str = double_as_string(cam->origin.y, 2)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_camvalue_two(t_text *msg, t_camera *cam)
{
	msg->pos.x = 125;
	msg->pos.y = 110;
	if (!(msg->str = double_as_string(cam->origin.z, 2)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 275;
	msg->pos.y = 65;
	if (!(msg->str = double_as_string(cam->direction.x, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_camvalue_three(t_text *msg, t_camera *cam)
{
	msg->pos.x = 275;
	msg->pos.y = 87;
	if (!(msg->str = double_as_string(cam->direction.y, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 275;
	msg->pos.y = 110;
	if (!(msg->str = double_as_string(cam->direction.z, 1)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	return (1);
}

int		draw_camera_value(t_text *msg, t_camera *cam)
{
	set_rgba_text(&(msg->bg_color), 0xE1E1E1);
	set_rgba_text(&(msg->fg_color), 0x0);
	if (!(draw_camvalue_one(msg, cam)))
		return (0);
	if (!(draw_camvalue_two(msg, cam)))
		return (0);
	if (!(draw_camvalue_three(msg, cam)))
		return (0);
	return (1);
}
