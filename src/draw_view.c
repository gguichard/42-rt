/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:09:54 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 12:58:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "raytracer.h"

void	draw_view(t_data *data)
{
	int	x;
	int	y;

	y = 50;
	while (y < 600)
	{
		x = 50;
		while (x < 150)
		{
			data->lib.view[y * data->winsize.width + x] = 0xFF0000;
			x++;
		}
		y++;
	}
}
