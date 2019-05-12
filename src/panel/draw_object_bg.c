/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:50:54 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/12 02:46:43 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "panel.h"

int		draw_effect_bg(t_text *msg)
{
	msg->pos.x = 693;
	msg->pos.y = 8;
	if (SDL_QueryTexture(msg->texture, NULL, NULL
			, &(msg->pos.w), &(msg->pos.h)) < 0)
		return (0);
	if (SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos)) < 0)
		return (0);
	return (1);
}

int		draw_attribute_bg(t_text *msg)
{
	msg->pos.x = 843;
	msg->pos.y = 8;
	if (SDL_QueryTexture(msg->texture, NULL, NULL
			, &(msg->pos.w), &(msg->pos.h)) < 0)
		return (0);
	if (SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos)) < 0)
		return (0);
	return (1);
}

int		draw_object_bg(t_text *msg)
{
	msg->pos.x = 342;
	msg->pos.y = 8;
	if (SDL_QueryTexture(msg->texture, NULL, NULL
			, &(msg->pos.w), &(msg->pos.h)) < 0)
		return (0);
	if (SDL_RenderCopy(msg->renderer, msg->texture, NULL, &(msg->pos)) < 0)
		return (0);
	return (1);
}

int		draw_obj_bg(t_data *data)
{
	t_text		msg;

	msg.renderer = data->lib.panel.renderer;
	msg.texture = data->lib.panel.light_bg;
	if (!(draw_attribute_bg(&(msg))))
		return (0);
	msg.texture = data->lib.panel.effect_bg;
	if (!(draw_effect_bg(&(msg))))
		return (0);
	msg.texture = data->lib.panel.object_bg;
	if (!(draw_object_bg(&(msg))))
		return (0);
	return (1);
}
