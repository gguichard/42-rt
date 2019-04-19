/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:10:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/19 10:30:35 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "SDL.h"
# include "error.h"
# include "winsize.h"

/*
** MACROS
*/

# define CAMERA_RIGHT (1)
# define CAMERA_LEFT (1 << 1)
# define CAMERA_DOWN (1 << 2)
# define CAMERA_UP (1 << 3)
# define CAMERA_TR_LEFT (1 << 4)
# define CAMERA_TR_RIGHT (1 << 5)
# define CAMERA_TR_FRONT (1 << 6)
# define CAMERA_TR_BACK (1 << 7)
# define CAMERA_TR_UP (1 << 8)
# define CAMERA_TR_DOWN (1 << 9)

/*
** TYPEDEF & STRUCTURES
*/

typedef struct s_data	t_data;

typedef struct		s_lib
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	unsigned int	cam_keys;
	unsigned int	*view;
}					t_lib;

/*
** PROTOTYPES
*/

t_error				init_and_create_window(t_lib *lib, t_winsize winsize);
void				run_event_loop(t_data *data, void (*draw_fn)(t_data *));
void				destroy_lib(t_lib *lib);

#endif
