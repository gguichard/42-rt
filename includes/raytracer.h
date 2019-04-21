/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:56:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/21 00:46:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "SDL.h"
# include "libft.h"
# include "lib.h"
# include "winsize.h"
# include "camera.h"
# include "ray_inf.h"
# include "vec3d.h"

# define GAMMA_CORRECTION .45454545454

typedef struct	s_data
{
	int			running;
	t_winsize	winsize;
	t_lib		lib;
	t_camera	camera;
	t_list		*objects;
	t_list		*lights;
	int			square_pixels_per_ray;
}				t_data;

t_vec3d			get_ray_dir(t_data *data, int x, int y);
int				has_object_in_ray(t_data *data, t_ray_inf *ray_inf
		, double max_dist);

void			trace_rays(t_data *data);
void			trace_light_rays(t_data *data, t_ray_inf *ray_inf);

#endif
