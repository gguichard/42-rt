/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:42:39 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/22 23:07:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_OBJECT_H
# define RAY_OBJECT_H

# include "vec3d.h"
# include "color.h"
# include "ray_inf.h"

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_PLANE 2
# define RAYOBJ_CYLINDER 3
# define RAYOBJ_CONE 4
# define RAYOBJ_TORUS 5
# define RAYOBJ_LIGHT 6
# define RAYOBJ_AMBIENTLIGHT 7

typedef struct		s_obj_rotation
{
	t_vec3d			vector;
	double			angle;
}					t_obj_rotation;

typedef struct		s_ray_object
{
	int				type;
	t_vec3d			origin;
	t_vec3d			vertices[3];
	t_color			color;
	t_obj_rotation	rotation;
	double			radius;
	double			big_radius;
	double			intensity;
	double			specular;
	double			shininess;
}					t_ray_object;

double				get_plane_intersect_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_cone_intersect_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_torus_intersect_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_sphere_intersect_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_cylinder_intersect_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);

double				get_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction);
t_vec3d				get_intersect_normal(t_ray_object *object
		, t_vec3d intersect);

#endif
