/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 22:44:19 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/07 06:45:43 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "panel.h"
#include <stdio.h>

int		write_text(t_text *msg, int size)
{
	/* a deplacer au debut du programme */ 
	if (TTF_Init() == -1)
		return (0);
	if (!(msg->police = TTF_OpenFont("/Library/Fonts/Arial Black.ttf", size)))
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
	SDL_QueryTexture(msg->texture, NULL, NULL, &(msg->pos.w), &(msg->pos.h));
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

int		draw_panel_main(t_data *data)
{
	t_text	msg;
	SDL_Surface *bg;

	msg.renderer = data->lib.panel.renderer;	
	if (!(bg = SDL_LoadBMP("src/panel/background/panel_bg.bmp")))
		return (0);
	msg.texture = SDL_CreateTextureFromSurface(msg.renderer, bg);
	SDL_FreeSurface(bg);
	msg.pos.x = 0;
	msg.pos.y = 0;
	msg.pos.w = 1000;
	msg.pos.h = 150;
	SDL_RenderCopy(msg.renderer, msg.texture, NULL, &(msg.pos));
	SDL_DestroyTexture(msg.texture);
	draw_camera_value(&msg, &(data->camera));
	return (1);

}
int		draw_panel_obj(t_data *data)
{
	draw_obj_bg(data);
	draw_obj_spatial(data);
	draw_obj_light(data);
	return (1);
}


int		draw_panel(t_data *data)
{
	if (!(draw_panel_main(data)))
		return (0);
	if (data->current)
		draw_panel_obj(data);
	SDL_RenderPresent(data->lib.panel.renderer);
	return (1);
}
