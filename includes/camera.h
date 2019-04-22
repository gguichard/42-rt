/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:56:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 21:41:04 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

/*
** INCLUDES
*/

# include "vec3d.h"
# include "SDL.h"

/*
** TYPEDEF & STRUCTURES
*/

typedef struct s_data	t_data;

typedef struct	s_camera
{
	double		fov;
	t_vec3d		origin;
	t_vec3d		direction;
	t_vec3d		up;
	t_vec3d		right;
}				t_camera;

/*
** PROTOTYPES
*/

void			rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle);
void			camera_press_key(SDL_Event *event, t_data *data);
void			camera_event(t_data *data);

#endif
