/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 05:19:30 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/08 06:32:54 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include "panel.h"
#include "raytracer.h"

SDL_Texture		*get_square_color(SDL_Renderer *renderer, int r, int g, int b)
{
	SDL_Surface *square;
	SDL_Texture	*texture;

	square = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);
	SDL_FillRect(square, NULL, SDL_MapRGB(square->format, r, g, b));
	texture = SDL_CreateTextureFromSurface(renderer, square);
	free(square);
	return (texture);
}

void			draw_wood_color(t_data *data)
{
	SDL_Texture	*texture;
	SDL_Rect	pos;

	texture = get_square_color(data->lib.panel.renderer,
			(int)(data->current->wood.color.x * 255.0),
			(int)(data->current->wood.color.y * 255.0),
			(int)(data->current->wood.color.z * 255.0));
	pos.x = 815;
	pos.y = 67;
	pos.w = 12;
	pos.h = 11;
	SDL_RenderCopy(data->lib.panel.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
}

void			draw_perlin_color(t_data *data)
{
	SDL_Texture	*texture;
	SDL_Rect	pos;

	texture = get_square_color(data->lib.panel.renderer,
			(int)(data->current->perlin.color.x * 255.0),
			(int)(data->current->perlin.color.y * 255.0),
			(int)(data->current->perlin.color.z * 255.0));
	pos.x = 815;
	pos.y = 91;
	pos.w = 12;
	pos.h = 11;
	SDL_RenderCopy(data->lib.panel.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
}

void			draw_checker_color(t_data *data)
{
	SDL_Texture	*texture;
	SDL_Rect	pos;

	texture = get_square_color(data->lib.panel.renderer,
			(int)(data->current->checker.color.x * 255.0),
			(int)(data->current->checker.color.y * 255.0),
			(int)(data->current->checker.color.z * 255.0));
	pos.x = 815;
	pos.y = 40;
	pos.w = 12;
	pos.h = 11;
	SDL_RenderCopy(data->lib.panel.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
}

void			draw_obj_color(t_data *data)
{
	SDL_Texture	*texture;
	SDL_Rect	pos;

	texture = get_square_color(data->lib.panel.renderer,
			(int)(data->current->color.x * 255.0),
			(int)(data->current->color.y * 255.0),
			(int)(data->current->color.z * 255.0));
	pos.x = 659;
	pos.y = 17;
	pos.w = 12;
	pos.h = 11;
	SDL_RenderCopy(data->lib.panel.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
}
