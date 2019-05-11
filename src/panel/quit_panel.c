/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:31:33 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/11 14:17:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	quit_panel_font(t_panel *panel)
{
	if (panel)
	{
		if (panel->arial_black_13)
		{
			TTF_CloseFont(panel->arial_black_13);
			panel->arial_black_13 = NULL;
		}
		if (panel->arial_black_12)
		{
			TTF_CloseFont(panel->arial_black_12);
			panel->arial_black_12 = NULL;
		}
		if (panel->arial_black_11)
		{
			TTF_CloseFont(panel->arial_black_11);
			panel->arial_black_11 = NULL;
		}
		if (panel->arial_black_9)
		{
			TTF_CloseFont(panel->arial_black_9);
			panel->arial_black_9 = NULL;
		}
		TTF_Quit();
	}
}

void	quit_panel(t_panel *panel)
{
	if (panel)
	{
		quit_panel_font(panel);
		if (panel->renderer)
		{
			SDL_DestroyRenderer(panel->renderer);
			panel->renderer = NULL;
		}
		if (panel->window)
		{
			SDL_DestroyWindow(panel->window);
			panel->window = NULL;
		}
	}
}
