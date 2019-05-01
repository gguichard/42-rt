/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_filter_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:14:09 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/01 16:55:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "effects.h"
#include "raytracer.h"
#include "ui.h"

void		filter_key_apply(SDL_Event *event, t_data *data)
{
	if (event->key.type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_r)
		{
			data->effect = NONE_FILTER;
			ui_refresh(data);
		}
		else if (event->key.keysym.sym == SDLK_g)
		{
			data->effect = GRAY_FILTER;
			ui_refresh(data);
		}
		else if (event->key.keysym.sym == SDLK_c)
		{
			data->effect = CARTOON_FILTER;
			ui_refresh(data);
		}
		else if (event->key.keysym.sym == SDLK_p)
			convert_to_ppm(data->lib.view, data);
	}
}
