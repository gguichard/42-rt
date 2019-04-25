/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:56:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/25 19:24:55 by gguichar         ###   ########.fr       */
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
# include "thread.h"
# include "vec3d.h"
# include "color.h"

# define NEAR_PLANE_CLIPPING 1e-4
# define SHADOW_BIAS 1e-4
# define GAMMA_CORRECTION .45454545454

typedef struct	s_data
{
	int			running;
	t_winsize	winsize;
	t_lib		lib;
	t_camera	camera;
	t_vector	objects;
	t_vector	lights;
	int			square_pixels_per_ray;
	t_thread	threads[MAX_THREADS];
}				t_data;

t_vec3d			get_ray_dir(t_data *data, int x, int y);

void			world_to_object_transform(t_ray_inf *ray_inf
		, t_ray_object *object, t_vec3d *origin, t_vec3d *direction);
int				has_object_in_ray(t_data *data, t_ray_inf *ray_inf
		, double max_dist_squared);

t_color			trace_reflect_ray(t_data *data, t_ray_inf *ray_inf, int depth);
t_color			trace_refract_ray(t_data *data, t_ray_inf *ray_inf, int depth);
t_color			trace_primary_ray(t_data *data, t_vec3d origin, t_vec3d ray_dir
		, int depth);

void			trace_rays(t_data *data);
void			trace_light_rays(t_data *data, t_ray_inf *ray_inf);

#endif
