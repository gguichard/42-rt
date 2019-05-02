/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:10:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 07:50:17 by ymekraou         ###   ########.fr       */
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
# define CAMERA_REVOLVE_R (1 << 10)
# define CAMERA_REVOLVE_L (1 << 11)

# define UI_SHAPE_LEFT (1)
# define UI_SHAPE_RIGHT (1 << 1)
# define UI_SHAPE_UP (1 << 2)
# define UI_SHAPE_DOWN (1 << 3)

# define PANEL_WIDTH 1000
# define PANEL_HEIGHT 100
/*
** TYPEDEF & STRUCTURES
*/

typedef struct s_data	t_data;

typedef struct		s_panel
{
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Renderer	*renderer;

}					t_panel;

typedef struct		s_lib
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_panel			panel;
	unsigned int	cam_keys;
	unsigned int	ui_keys;
	unsigned int	*view;
}					t_lib;

/*
** PROTOTYPES
*/

t_error				init_and_create_window(t_lib *lib, t_winsize winsize);
void				run_event_loop(t_data *data);
void				destroy_lib(t_lib *lib);
int					draw_panel(t_lib *lib);
#endif
