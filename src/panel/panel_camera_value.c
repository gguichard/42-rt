/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_camera_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:27:43 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/09 09:42:14 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ft_sprintf.h"
#include "panel.h"
#include "vec3d.h"
#include <math.h>

void	draw_camera_pos_value(t_text *msg, t_camera *cam)
{
	msg->pos.x = 125;
	msg->pos.y = 65;
	msg->str = ft_sprintf("%.2lf", cam->origin.x);
	write_text(msg, 12);
	free(msg->str);
	msg->pos.x = 125;
	msg->pos.y = 87;
	msg->str = ft_sprintf("%.2lf", cam->origin.y);
	write_text(msg, 12);
	free(msg->str);
	msg->pos.x = 125;
	msg->pos.y = 110;
	msg->str = ft_sprintf("%.2lf", cam->origin.z);
	write_text(msg, 12);
	free(msg->str);
}

void	compute_cam_angle(double angle[3], t_camera *cam)
{
	t_vec3d		axe;
	double		res;

	axe = vec3d(1, 0, 0);
	axe = vec3d_unit(axe);
	res = vec3d_dot(cam->direction, axe);
	angle[0] = acos(res) * (180.0 / M_PI);
//	if (cam->direction.z > 0)
//		angle[0] *= (-1); 
	axe = vec3d(0, 1, 0);
	axe = vec3d_unit(axe);
	res = vec3d_dot(cam->up, axe);
	angle[1] = acos(res) * (180.0 / M_PI);
//	if (cam->direction.z < 0)
//		angle[1] *= (-1); 
	axe = vec3d(0, 0, 1);
	res = vec3d_dot(cam->up, axe);
	angle[2] = acos(res) * (180.0 / M_PI);
//	if (cam->direction.y < 0)
//		angle[2] *= (-1); 
}

void	draw_camera_angle_value(t_text *msg, t_camera *cam)
{
	double	angle[3];

	compute_cam_angle(angle, cam);
	msg->pos.x = 275;
	msg->pos.y = 65;
	msg->str = ft_sprintf("%.1lf", angle[0]);
	write_text(msg, 12);
	free(msg->str);
	msg->pos.x = 275;
	msg->pos.y = 87;
	msg->str = ft_sprintf("%.1lf", angle[1]);
	write_text(msg, 12);
	free(msg->str);
	msg->pos.x = 275;
	msg->pos.y = 110;
	msg->str = ft_sprintf("%.1lf", angle[2]);
	write_text(msg, 12);
	free(msg->str);
}

void	draw_camera_value(t_text *msg, t_camera *cam)
{
	set_rgba_text(&(msg->bg_color), 0xE1E1E1);
	set_rgba_text(&(msg->fg_color), 0x0);
	draw_camera_pos_value(msg, cam);
	draw_camera_angle_value(msg, cam);
}
