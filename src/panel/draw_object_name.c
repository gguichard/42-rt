/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_object_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 01:12:15 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/08 03:44:19 by ymekraou         ###   ########.fr       */
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

void	draw_obj_color(t_data *data)
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

char	*get_obj_type(int id)
{
	if (id == 1)
		return ("SPHERE");
	if (id == 2)
		return ("PLAN");
	if (id == 3)
		return ("CYLENDER");
	if (id == 4)
		return ("CONE");
	if (id == 5)
		return ("TORUS");
	if (id == 6)
		return ("TRIANGLE");
	if (id == 7)
		return ("ELLIPSOID");
	if (id == 8)
		return ("HYPERBOLOID");
	if (id == 9)
		return ("TANGLECUBE");
	return ("UNKNOWN");
}

void	draw_obj_name(t_data *data)
{
	t_text	msg;

	msg.renderer = data->lib.panel.renderer;
	set_rgba_text(&(msg.bg_color),0xA6A6A6);
	set_rgba_text(&(msg.fg_color),0xFF0000);
	msg.pos.x = 490;
	msg.pos.y = 12;	
	msg.str = get_obj_type(data->current->type);
	write_text(&(msg), 13);
}
