/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:56:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/09 20:00:50 by gguichar         ###   ########.fr       */
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
# include "ray_object.h"

# define NEAR_PLANE_CLIPPING 1e-4
# define SHADOW_BIAS 1e-4

# define NONE_FILTER (0)
# define GRAY_FILTER (1)
# define CARTOON_FILTER (1 << 1)
# define PERLIN_FILTER (1 << 2)

typedef struct	s_data
{
	int				running;
	t_winsize		winsize;
	t_lib			lib;
	t_camera		camera;
	t_vector		objects;
	t_vector		lights;
	int				sampling;
	double			fog;
	int				effect;
	t_thread		threads[MAX_THREADS];
	t_ray_object	*current;
}				t_data;

t_vec3d			get_ray_dir(t_data *data, int x, int y);

void			world_to_object_transform(t_ray_object *object
	, t_ray_inf *ray_inf, t_ray_hit *hit);
int				has_object_in_ray(t_data *data, t_ray_inf *ray_inf
	, double max_dist_squared);

void			intersect_primary_ray(t_data *data, t_ray_inf *ray_inf);

t_vec3d			trace_reflect_ray(t_data *data, t_ray_inf *ray_inf, int depth);
t_vec3d			trace_refract_ray(t_data *data, t_ray_inf *ray_inf, int depth);
t_vec3d			trace_primary_ray(t_data *data, t_vec3d origin, t_vec3d ray_dir
	, int depth);
t_vec3d			trace_light_rays(t_data *data, t_ray_inf *ray_inf
	, t_vec3d base_color);

void			draw_trace_rays(t_data *data);

int				convert_to_ppm(unsigned int *view, t_data *data);

#endif
