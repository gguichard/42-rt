/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:40:08 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/12 02:49:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "panel.h"

int		init_panel_font(t_panel *panel)
{
	if (TTF_Init() == -1)
		return (0);
	if (!(panel->arial_black_13 = TTF_OpenFont("/Library/Fonts/Arial Black.ttf"
					, 13)))
		return (0);
	if (!(panel->arial_black_12 = TTF_OpenFont("/Library/Fonts/Arial Black.ttf"
					, 12)))
		return (0);
	if (!(panel->arial_black_11 = TTF_OpenFont("/Library/Fonts/Arial Black.ttf"
					, 11)))
		return (0);
	if (!(panel->arial_black_9 = TTF_OpenFont("/Library/Fonts/Arial Black.ttf"
					, 9)))
		return (0);
	return (1);
}

int		init_panel_texture(t_panel *panel)
{
	SDL_Surface	*surface;

	surface = NULL;
	if (!(surface = SDL_LoadBMP("src/panel/background/panel_bg.bmp")))
		return (0);
	panel->panel_bg = SDL_CreateTextureFromSurface(panel->renderer, surface);
	SDL_FreeSurface(surface);
	surface = NULL;
	if (!(surface = SDL_LoadBMP("src/panel/background/light_bg.bmp")))
		return (0);
	panel->light_bg = SDL_CreateTextureFromSurface(panel->renderer, surface);
	SDL_FreeSurface(surface);
	surface = NULL;
	if (!(surface = SDL_LoadBMP("src/panel/background/effect_bg.bmp")))
		return (0);
	panel->effect_bg = SDL_CreateTextureFromSurface(panel->renderer, surface);
	SDL_FreeSurface(surface);
	surface = NULL;
	if (!(surface = SDL_LoadBMP("src/panel/background/object_bg.bmp")))
		return (0);
	panel->object_bg = SDL_CreateTextureFromSurface(panel->renderer, surface);
	SDL_FreeSurface(surface);
	return (1);
}

int		init_panel(t_panel *panel)
{
	if (SDL_CreateWindowAndRenderer(PANEL_WIDTH, PANEL_HEIGHT
			, 0, &(panel->window), &(panel->renderer)) < 0)
		return (0);
	SDL_SetWindowPosition(panel->window, 800, 117);
	SDL_SetWindowTitle(panel->window, "RT - parameters");
	if (!(init_panel_texture(panel)))
		return (0);
	if (!(init_panel_font(panel)))
		return (0);
	return (1);
}
