/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_transforms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 00:41:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 03:46:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "ui.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"
#include "math_utils.h"
#include "quaternion.h"

void		ui_select_object(t_data *data, SDL_Event *event)
{
	t_vec3d		ray_dir;
	t_ray_inf	ray_inf;

	if (event->button.button == SDL_BUTTON_RIGHT)
		data->current = NULL;
	else if (event->button.button == SDL_BUTTON_LEFT)
	{
		ray_dir = get_ray_dir(data, event->button.x, event->button.y);
		ray_inf.origin = data->camera.origin;
		ray_inf.direction = ray_dir;
		ray_inf.object = NULL;
		intersect_primary_ray(data, &ray_inf);
		data->current = ray_inf.object;
	}
}

void		ui_radius_shape(t_data *data, SDL_Event *event)
{
	if (data->current != NULL)
	{
		data->current->radius += clamp(event->wheel.y, -1.5, 1.5);
		if (data->current->radius < 0)
			data->current->radius = 1;
		ui_refresh(data);
	}
}

void		ui_translate_shape(t_data *data, t_vec3d direction)
{
	t_ray_object	*object;

	object = data->current;
	if (object != NULL)
	{
		object->origin = vec3d_add(object->origin, direction);
		ui_refresh(data);
	}
}

void		ui_rotate_shape(t_data *data, t_vec3d rotation, double angle)
{
	t_ray_object	*object;

	object = data->current;
	if (object != NULL)
	{
		if (data->lib.ui_keys & UI_SHAPE_SHIFT)
			angle = -angle;
		object->rot_quat = quaternion_mul(object->rot_quat
				, vec3d_to_rotate_quaternion(rotation, angle));
		object->inv_rot_quat = quaternion_conj(object->rot_quat);
		ui_refresh(data);
	}
}
