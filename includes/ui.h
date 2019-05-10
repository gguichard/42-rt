/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 00:45:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 03:33:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "SDL.h"
# include "raytracer.h"
# include "vec3d.h"

void	ui_select_object(t_data *data, SDL_Event *event);
void	ui_radius_shape(t_data *data, SDL_Event *event);
void	ui_translate_shape(t_data *data, t_vec3d direction);
void	ui_rotate_shape(t_data *data, t_vec3d rotation, double angle);

void	ui_loop_keys(t_data *data);
void	ui_shapes_keys(SDL_Event *event, t_data *data);

void	ui_refresh(t_data *data);

void	draw_texture(t_data *data);

#endif
