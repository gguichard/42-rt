/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 22:44:19 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/03 08:13:35 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "panel.h"

int		write_text(t_text *msg)
{
	/* a deplacer au debut du programme */ 
	if (TTF_Init() == -1)
		return (0);
	if (!(msg->police = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20)))
	{
		TTF_Quit();
		return (0);
	}

	/* function core a conserver */
	if(!(msg->texte = TTF_RenderText_Shaded(msg->police, msg->str, msg->fg_color, msg->bg_color)))
	{
		TTF_CloseFont(msg->police);
		TTF_Quit();
		return (0);	
	}
	msg->texture = SDL_CreateTextureFromSurface(msg->renderer, msg->texte);
	SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos));
	SDL_FreeSurface(msg->texte);
	SDL_DestroyTexture(msg->texture);

	/* a deplacer a la fin du programme */ 
	TTF_CloseFont(msg->police); 
	TTF_Quit();
	return (1);
}

void	set_rgba_text(SDL_Color *color, int value)
{
	color->a = value % (16 * 16);
	value /= (16 * 16);
	color->b = value % (16 * 16);
	value /= (16 * 16);
	color->g = value % (16 * 16);
	value /= (16 * 16);
	color->r = value % (16 * 16);
}


int		draw_panel(t_data *data)
{
	t_text	msg;
	
	SDL_SetRenderDrawColor(data->lib->panel.renderer, 0x87, 0x83, 0x7d, 0);
	SDL_RenderClear(data->lib->panel.renderer);

	msg.renderer = data->lib->panel.renderer;	
	draw_camera_menu(&msg);
	SDL_RenderPresent(data->lib->panel.renderer);

	return (1);
}
