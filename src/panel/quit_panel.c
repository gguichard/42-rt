/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:31:33 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/09 13:07:54 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int		quit_panel_font(t_panel *panel)
{
	if (panel && ((panel->arial_black_13) || (panel->arial_black_13)
				|| (panel->arial_black_13) || (panel->arial_black_13)))
	{
		if (panel->arial_black_13)
			TTF_CloseFont(panel->arial_black_13);
		if (panel->arial_black_12)
			TTF_CloseFont(panel->arial_black_12);
		if (panel->arial_black_11)
			TTF_CloseFont(panel->arial_black_11);
		if (panel->arial_black_9)
			TTF_CloseFont(panel->arial_black_9);
		TTF_Quit();
	}
	return (0);
}

void	quit_panel(t_panel *panel)
{
	if (panel)
	{
		quit_panel_font(panel);
		if (panel->renderer)
			SDL_DestroyRenderer(panel->renderer);
		if (panel->window)
			SDL_DestroyWindow(panel->window);
	}
}
