/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:02:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/29 02:16:15 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "lib.h"
#include "ui.h"
#include "raytracer.h"
#include "perturbations.h"
#include "camera.h"

void		draw_texture(t_data *data)
{
	int	pitch;

	if (SDL_LockTexture(data->lib.texture, NULL
				, (void **)&data->lib.view, &pitch) == 0)
	{
		draw_trace_rays(data);
		SDL_UnlockTexture(data->lib.texture);
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		SDL_RenderPresent(data->lib.renderer);
	}
}

static void	handle_loop(t_data *data)
{
	ui_loop_keys(data);
	if (data->lib.cam_keys == 0 && data->sampling > 1)
		data->sampling /= 2;
	if (data->lib.cam_keys != 0)
		data->sampling = 16;
	camera_event(data);
	if (data->sampling > 0)
	{
		draw_texture(data);
		if (data->sampling == 1)
			data->sampling = 0;
	}
}

void		run_event_loop(t_data *data)
{
	SDL_Event	event;

	data->running = 1;
	while (data->running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT
					|| (event.type == SDL_KEYDOWN
						&& event.key.keysym.sym == SDLK_ESCAPE))
			{
				data->running = 0;
				break ;
			}
			ui_shapes_keys(&event, data);
			camera_press_key(&event, data);
			filter_key_apply(&event, data);
		}
		if (data->running)
			handle_loop(data);
	}
}
