/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 11:55:24 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/18 15:06:38 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "vec3d.h"
#include "lib.h"

void		camera_event(SDL_Event *event, t_camera *camera)
{
	if (event->key.keysym.sym == SDLK_KP_4)
		rotate_camera(camera, (t_vec3d){0, 1, 0}, M_PI / 90);
	if (event->key.keysym.sym == SDLK_KP_6)
		rotate_camera(camera, (t_vec3d){0, 1, 0}, -1 * M_PI / 90);
	if (event->key.keysym.sym == SDLK_KP_2)
		rotate_camera(camera, (t_vec3d){1, 0, 0}, M_PI / 90);
	if (event->key.keysym.sym == SDLK_KP_8)
		rotate_camera(camera, (t_vec3d){1, 0, 0}, -1 * M_PI / 90);
	if (event->key.keysym.sym == SDLK_KP_7)
		rotate_camera(camera, (t_vec3d){0, 0, 1}, M_PI / 90);
	if (event->key.keysym.sym == SDLK_KP_3)
		rotate_camera(camera, (t_vec3d){0, 0, 1}, -1 * M_PI / 90);
	if (event->key.keysym.sym == SDLK_UP)
		camera->origin = vec3d_add(camera->origin, camera->direction);
	if (event->key.keysym.sym == SDLK_DOWN)
		camera->origin = vec3d_sub(camera->origin, camera->direction);
}
