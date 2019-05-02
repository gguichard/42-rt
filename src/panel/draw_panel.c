/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 22:44:19 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/02 23:13:38 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "../../SDL_text/ttf_build/include/SDL2/SDL_ttf.h"

void	panel_background(SDL_Surface *screen)
{
	int i;
	int area;
	
	area = (int)(PANEL_WIDTH * PANEL_HEIGHT);
	
	i = -1;
	while (++i < area)
		((int*)(screen->pixels))[i]= 0x00FEDCC1;
}

int		test(t_lib *lib)
{
	TTF_Font *police;
	SDL_Surface *texte;
	SDL_Color Noire = {0, 0, 0, 0};
	SDL_Color Blanche = {255, 255, 255, 255};
	SDL_Texture *texture;
//	SDL_Rect rect;
	char *str;

	if (TTF_Init() == -1)
		return (0);
	if (!(police = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20)))
		return (0); //proper quit to do
	str = "hello world";
	if(!(texte = TTF_RenderText_Shaded(police, str, Noire, Blanche)))
		printf("samere");
	texture = SDL_CreateTextureFromSurface(lib->panel.renderer, texte);
	SDL_Rect rect1 = {20, 10, 100, 20};
	SDL_RenderCopy(lib->panel.renderer, texture, NULL, &rect1);
	SDL_FreeSurface(texte);
	TTF_CloseFont(police);
	TTF_Quit();
	return (1);
}

int		draw_panel(t_lib *lib)
{
	SDL_SetRenderDrawColor(lib->panel.renderer, 0xF2, 0xE7, 0xBF, 0);
	SDL_RenderClear(lib->panel.renderer);
	test(lib);

	SDL_RenderPresent(lib->panel.renderer);
	return (1);
}
