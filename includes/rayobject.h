/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayobject.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:11:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 16:26:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYOBJECT_H
# define RAYOBJECT_H

# include "vec3d.h"
# include "camera.h"

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_LIGHT 2

typedef struct	s_ray_object
{
	int				type;
	t_vec3d			origin;
	t_vec3d			rotation;
	unsigned int	color;
	double			radius;
}				t_ray_object;

double			get_sphere_intersect(t_camera *camera, t_vec3d ray_dir
		, t_ray_object *obj);

#endif
