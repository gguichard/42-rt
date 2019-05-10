/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:50:06 by ymekraou          #+#    #+#             */
/*   Updated: 2019/05/10 18:58:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PANEL_H
# define PANEL_H

# include "SDL_ttf.h"
# include "SDL.h"
# include "error.h"
# include "winsize.h"
# include "lib.h"
# include "camera.h"

/*
** MACROS
*/

# define PANEL_WIDTH 1000
# define PANEL_HEIGHT 150

/*
** TYPEDEF & STRUCTURES
*/

typedef struct		s_text
{
	char			*str;
	SDL_Rect		pos;
	SDL_Color		fg_color;
	SDL_Color		bg_color;
	SDL_Surface		*texte;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	TTF_Font		*police;
}					t_text;

/*
** PROTOTYPES
*/

int					write_text(t_text *msg);
void				set_rgba_text(SDL_Color *color, int value);
int					draw_obj_name(t_data *data);
int					draw_obj_bg(t_data *data);
int					draw_obj_spatial(t_data *data);
int					draw_obj_color(t_data *data);
int					draw_wood_color(t_data *data);
int					draw_perlin_color(t_data *data);
int					draw_checker_color(t_data *data);
int					draw_obj_light(t_data *data);
int					draw_obj_effect(t_data *data);
int					draw_camera_value(t_text *msg, t_camera *cam);

char				*double_as_string(double value, unsigned int precision);

#endif
