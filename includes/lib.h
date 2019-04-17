/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:10:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 12:21:31 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "SDL.h"
# include "error.h"
# include "winsize.h"

typedef struct s_data	t_data;

typedef struct	s_lib
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	unsigned int	*view;
}				t_lib;

t_error	init_and_create_window(t_lib *lib, t_winsize winsize);
void	run_event_loop(t_data *data, void (*draw_fn)(t_data *));
void	destroy_lib(t_lib *lib);

#endif
