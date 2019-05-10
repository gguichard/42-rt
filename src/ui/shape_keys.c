/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 00:34:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 03:47:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "SDL.h"
#include "raytracer.h"
#include "ui.h"

void		ui_loop_keys(t_data *data)
{
	if (data->lib.ui_keys & UI_SHAPE_LEFT)
		ui_translate_shape(data, vec3d_scalar(data->camera.right, -1));
	if (data->lib.ui_keys & UI_SHAPE_RIGHT)
		ui_translate_shape(data, data->camera.right);
	if (data->lib.ui_keys & UI_SHAPE_UP)
		ui_translate_shape(data, vec3d(0, 1, 0));
	if (data->lib.ui_keys & UI_SHAPE_DOWN)
		ui_translate_shape(data, vec3d(0, -1, 0));
	if (data->lib.ui_keys & UI_SHAPE_ROTX)
		ui_rotate_shape(data, vec3d(1, 0, 0), M_PI / 180.);
	if (data->lib.ui_keys & UI_SHAPE_ROTY)
		ui_rotate_shape(data, vec3d(0, 1, 0), M_PI / 180.);
	if (data->lib.ui_keys & UI_SHAPE_ROTZ)
		ui_rotate_shape(data, vec3d(0, 0, 1), M_PI / 180.);
}

static void	ui_shapes_keyup(t_data *data, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_KP_4)
		data->lib.ui_keys &= ~UI_SHAPE_LEFT;
	else if (event->key.keysym.sym == SDLK_KP_6)
		data->lib.ui_keys &= ~UI_SHAPE_RIGHT;
	else if (event->key.keysym.sym == SDLK_KP_8)
		data->lib.ui_keys &= ~UI_SHAPE_UP;
	else if (event->key.keysym.sym == SDLK_KP_2)
		data->lib.ui_keys &= ~UI_SHAPE_DOWN;
	else if (event->key.keysym.sym == SDLK_KP_3)
		data->lib.ui_keys &= ~UI_SHAPE_ROTX;
	else if (event->key.keysym.sym == SDLK_KP_1)
		data->lib.ui_keys &= ~UI_SHAPE_ROTY;
	else if (event->key.keysym.sym == SDLK_KP_7)
		data->lib.ui_keys &= ~UI_SHAPE_ROTZ;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		data->lib.ui_keys &= ~UI_SHAPE_SHIFT;
}

static void	ui_shapes_keydown(t_data *data, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_KP_4)
		data->lib.ui_keys |= UI_SHAPE_LEFT;
	else if (event->key.keysym.sym == SDLK_KP_6)
		data->lib.ui_keys |= UI_SHAPE_RIGHT;
	else if (event->key.keysym.sym == SDLK_KP_8)
		data->lib.ui_keys |= UI_SHAPE_UP;
	else if (event->key.keysym.sym == SDLK_KP_2)
		data->lib.ui_keys |= UI_SHAPE_DOWN;
	else if (event->key.keysym.sym == SDLK_KP_3)
		data->lib.ui_keys |= UI_SHAPE_ROTX;
	else if (event->key.keysym.sym == SDLK_KP_1)
		data->lib.ui_keys |= UI_SHAPE_ROTY;
	else if (event->key.keysym.sym == SDLK_KP_7)
		data->lib.ui_keys |= UI_SHAPE_ROTZ;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		data->lib.ui_keys |= UI_SHAPE_SHIFT;
}

void		ui_shapes_keys(SDL_Event *event, t_data *data)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		ui_select_object(data, event);
	else if (data->current != NULL)
	{
		if (event->type == SDL_MOUSEWHEEL)
			ui_radius_shape(data, event);
		else if (event->type == SDL_KEYDOWN)
			ui_shapes_keydown(data, event);
		else if (event->type == SDL_KEYUP)
			ui_shapes_keyup(data, event);
	}
}
