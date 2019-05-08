/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:50:54 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/08 06:30:14 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "panel.h"

int		draw_effect_bg(t_text *msg, SDL_Surface *bg)
{
	if (!(bg = SDL_LoadBMP("src/panel/background/effect_attribute.bmp")))
		return (0);
	msg->texture = SDL_CreateTextureFromSurface(msg->renderer, bg);
	SDL_FreeSurface(bg);
	msg->pos.x = 693;
	msg->pos.y = 8;
	SDL_QueryTexture(msg->texture, NULL, NULL, &(msg->pos.w), &(msg->pos.h));
	SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos));
	SDL_DestroyTexture(msg->texture);
	return (1);
}

int		draw_attribute_bg(t_text *msg, SDL_Surface *bg)
{
	if (!(bg = SDL_LoadBMP("src/panel/background/attribute.bmp")))
		return (0);
	msg->texture = SDL_CreateTextureFromSurface(msg->renderer, bg);
	SDL_FreeSurface(bg);
	msg->pos.x = 843;
	msg->pos.y = 8;
	SDL_QueryTexture(msg->texture, NULL, NULL, &(msg->pos.w), &(msg->pos.h));
	SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos));
	SDL_DestroyTexture(msg->texture);
	return (1);
}

int		draw_object_bg(t_text *msg, SDL_Surface *bg)
{
	if (!(bg = SDL_LoadBMP("src/panel/background/object.bmp")))
		return (0);
	msg->texture = SDL_CreateTextureFromSurface(msg->renderer, bg);
	SDL_FreeSurface(bg);
	msg->pos.x = 342;
	msg->pos.y = 8;
	SDL_QueryTexture(msg->texture, NULL, NULL, &(msg->pos.w), &(msg->pos.h));
	SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos));
	SDL_DestroyTexture(msg->texture);
	return (1);
}

int		draw_obj_bg(t_data *data)
{
	t_text		msg;
	SDL_Surface	*bg;

	bg = NULL;
	msg.renderer = data->lib.panel.renderer;
	if (!(draw_attribute_bg(&(msg), bg)))
		return (0);
	if (!(draw_effect_bg(&(msg), bg)))
		return (0);
	if (!(draw_object_bg(&(msg), bg)))
		return (0);
	return (1);
}
