/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_filter_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:14:09 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/29 02:18:26 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "raytracer.h"

void		filter_key_apply(SDL_Event *event, t_data *data)
{
	if (event->key.type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_r)
			data->effect = NONE_FILTER;
		if (event->key.keysym.sym == SDLK_g)
			data->effect = GRAY_FILTER;
		if (event->key.keysym.sym == SDLK_c)
			data->effect = CARTOON_FILTER;
	}
}
