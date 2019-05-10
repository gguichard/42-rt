/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_camera_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:27:43 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/09 17:58:30 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"

int		draw_camvalue_one(t_text *msg, t_camera *cam)
{
	msg->pos.x = 125;
	msg->pos.y = 65;
	if (!(msg->str = ft_sprintf("%.2lf", cam->origin.x)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 125;
	msg->pos.y = 87;
	if (!(msg->str = ft_sprintf("%.2lf", cam->origin.y)))
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
	if (!(msg->str = ft_sprintf("%.2lf", cam->origin.z)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 275;
	msg->pos.y = 65;
	if (!(msg->str = ft_sprintf("%.1lf", cam->direction.x)))
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
	if (!(msg->str = ft_sprintf("%.1lf", cam->direction.y)))
		return (0);
	if (!(write_text(msg)))
	{
		free(msg->str);
		return (0);
	}
	free(msg->str);
	msg->pos.x = 275;
	msg->pos.y = 110;
	if (!(msg->str = ft_sprintf("%.1lf", cam->direction.z)))
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
