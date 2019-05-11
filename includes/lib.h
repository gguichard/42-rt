/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:10:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 14:17:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "SDL.h"
# include "error.h"
# include "winsize.h"
# include "panel.h"

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
# define UI_SHAPE_ROTX (1 << 4)
# define UI_SHAPE_ROTY (1 << 5)
# define UI_SHAPE_ROTZ (1 << 6)
# define UI_SHAPE_SHIFT (1 << 7)

/*
** TYPEDEF & STRUCTURES
*/

typedef struct s_data	t_data;

typedef struct		s_panel
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*arial_black_13;
	TTF_Font		*arial_black_12;
	TTF_Font		*arial_black_11;
	TTF_Font		*arial_black_9;
	SDL_Texture		*panel_bg;
	SDL_Texture		*light_bg;
	SDL_Texture		*effect_bg;
	SDL_Texture		*object_bg;
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
void				quit_panel(t_panel *panel);
void				quit_panel_font(t_panel *panel);
int					init_panel(t_panel *panel);
int					draw_panel(t_data *data);
#endif
