/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 22:44:19 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/03 09:58:00 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "panel.h"

int		write_text(t_text *msg)
{
	/* a deplacer au debut du programme */ 
	if (TTF_Init() == -1)
		return (0);
	if (!(msg->police = TTF_OpenFont("/Library/Fonts/Arial.ttf", 15)))
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
	color->b = value % (256);
	value /= (256);
	color->g = value % (256);
	value /= (256);
	color->r = value % (256);
	value /= (256);
	color->a = 0;
}


int		draw_panel(t_data *data)
{
	t_text	msg;
	
	SDL_SetRenderDrawColor(data->lib.panel.renderer, 0x87, 0x83, 0x7d, 0);
	SDL_RenderClear(data->lib.panel.renderer);

	msg.renderer = data->lib.panel.renderer;	
	draw_camera_menu(&msg);	
	draw_camera_value(&msg, &(data->camera));
	SDL_RenderPresent(data->lib.panel.renderer);

	return (1);
}
