/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:04:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/19 10:49:50 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"
#include "camera.h"

static void	destroy_window(t_lib *lib)
{
	if (lib->texture != NULL)
	{
		SDL_DestroyTexture(lib->texture);
		lib->texture = NULL;
	}
	if (lib->renderer != NULL)
	{
		SDL_DestroyRenderer(lib->renderer);
		lib->renderer = NULL;
	}
	if (lib->window != NULL)
	{
		SDL_DestroyWindow(lib->window);
		lib->window = NULL;
	}
}

t_error		init_and_create_window(t_lib *lib, t_winsize winsize)
{
	t_error	err;

	err = ERR_NOERROR;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		err = ERR_SDLINIT;
	if (err == ERR_NOERROR
			&& (lib->window = SDL_CreateWindow(WIN_TITLE
					, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
					, winsize.width, winsize.height, 0)) == NULL)
		err = ERR_SDLINIT;
	if (err == ERR_NOERROR
			&& (lib->renderer = SDL_CreateRenderer(lib->window, -1, SDL_RENDERER_PRESENTVSYNC)) == NULL)
		err = ERR_SDLINIT;
	if (err == ERR_NOERROR
			&& (lib->texture = SDL_CreateTexture(lib->renderer
					, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
					, winsize.width, winsize.height)) == NULL)
		err = ERR_SDLINIT;
	if (err != ERR_NOERROR)
		destroy_window(lib);
	return (err);
}

void		run_event_loop(t_data *data, void (*draw_fn)(t_data *))
{
	SDL_Event	event;
	int			pitch;

	data->running = 1;
	while (data->running)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				break ;
			camera_press_key(&event, data);
		}
		camera_event(data);
		if (SDL_LockTexture(data->lib.texture, NULL
					, (void **)&data->lib.view, &pitch) < 0)
			break ;
		draw_fn(data);
		SDL_UnlockTexture(data->lib.texture);
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		SDL_RenderPresent(data->lib.renderer);
	}
	data->running = 0;
}

void		destroy_lib(t_lib *lib)
{
	destroy_window(lib);
	SDL_Quit();
}
