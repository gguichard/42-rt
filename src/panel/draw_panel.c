/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 22:44:19 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/12 02:50:09 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "panel.h"

int		write_text(t_text *msg)
{
	if (!(msg->texte = TTF_RenderText_Shaded(msg->police, msg->str
					, msg->fg_color, msg->bg_color)))
		return (0);
	if (!(msg->texture = SDL_CreateTextureFromSurface(msg->renderer
					, msg->texte)))
	{
		SDL_FreeSurface(msg->texte);
		return (0);
	}
	SDL_FreeSurface(msg->texte);
	if (SDL_QueryTexture(msg->texture, NULL, NULL
				, &(msg->pos.w), &(msg->pos.h)) < 0)
	{
		SDL_DestroyTexture(msg->texture);
		return (0);
	}
	if (SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos)) < 0)
	{
		SDL_DestroyTexture(msg->texture);
		return (0);
	}
	SDL_DestroyTexture(msg->texture);
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
	t_text		msg;

	msg.renderer = data->lib.panel.renderer;
	msg.texture = data->lib.panel.panel_bg;
	msg.pos.x = 0;
	msg.pos.y = 0;
	msg.pos.w = 1000;
	msg.pos.h = 150;
	if (SDL_RenderCopy(msg.renderer, msg.texture, NULL, &(msg.pos)) < 0)
		return (0);
	msg.police = data->lib.panel.arial_black_12;
	if (!(draw_camera_value(&msg, &(data->camera))))
		return (0);
	return (1);
}

int		draw_panel_obj(t_data *data)
{
	if (!(draw_obj_bg(data)))
		return (0);
	if (!(draw_obj_name(data)))
		return (0);
	if (!(draw_obj_color(data)))
		return (0);
	if (!(draw_obj_spatial(data)))
		return (0);
	if (!(draw_obj_light(data)))
		return (0);
	if (!(draw_obj_effect(data)))
		return (0);
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
