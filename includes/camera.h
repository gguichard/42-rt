/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:56:10 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 14:45:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vec3d.h"

typedef struct	s_camera
{
	int			fov;
	t_vec3d		pos;
	t_vec3d		direction;
}				t_camera;

#endif
