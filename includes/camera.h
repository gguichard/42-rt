/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:56:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 12:29:12 by roduquen         ###   ########.fr       */
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

typedef struct	s_camera
{
	int			fov;
	t_vec3d		origin;
	t_vec3d		direction;
	t_vec3d		up;
	t_vec3d		right;
}				t_camera;

/*
** PROTOTYPES
*/

t_vec3d			rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle);
void			camera_event(SDL_Event *event, t_camera *camera);

#endif
