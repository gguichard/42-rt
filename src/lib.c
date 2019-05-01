/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:04:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/01 16:00:47 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"

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
		&& (lib->renderer = SDL_CreateRenderer(lib->window, -1
					, SDL_RENDERER_PRESENTVSYNC)) == NULL)
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

void		destroy_lib(t_lib *lib)
{
	destroy_window(lib);
	SDL_Quit();
}
