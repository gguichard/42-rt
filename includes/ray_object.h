/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:42:39 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 02:36:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_OBJECT_H
# define RAY_OBJECT_H

# include "vec3d.h"
# include "ray_inf.h"
# include "quaternion.h"

# define EPSILON 1e-6

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_PLANE 2
# define RAYOBJ_CYLINDER 3
# define RAYOBJ_CONE 4
# define RAYOBJ_TORUS 5
# define RAYOBJ_TRIANGLE 6
# define RAYOBJ_ELLIPSOID 7
# define RAYOBJ_HYPERBOLOID 8
# define RAYOBJ_TANGLECUBE 9
# define RAYOBJ_LIGHT 10
# define RAYOBJ_AMBIENTLIGHT 11

typedef struct s_ray_object	t_ray_object;

typedef struct		s_obj_checker
{
	t_vec3d			color;
	double			size;
}					t_obj_checker;

typedef struct		s_obj_perlin
{
	int				enabled;
	t_vec3d			color;
}					t_obj_perlin;

typedef struct		s_obj_wood
{
	int				enabled;
	t_vec3d			color;
}					t_obj_wood;

typedef struct		s_cut_plane
{
	char			on_xmax;
	char			on_xmin;
	char			on_ymax;
	char			on_ymin;
	char			on_zmax;
	char			on_zmin;
	t_vec3d			min;
	t_vec3d			max;
}					t_cut_plane;

typedef struct		s_ray_hit
{
	t_vec3d			origin;
	t_vec3d			direction;
	double			dist;
	t_vec3d			normal;
	int				inside;
}					t_ray_hit;

struct				s_ray_object
{
	int				type;
	void			(*intersect)(t_ray_object *, t_ray_hit *);
	t_cut_plane		cut_plane;
	t_vec3d			origin;
	t_vec3d			rotation;
	t_vec3d			vertices[3];
	t_vec3d			size;
	t_vec3d			color;
	t_obj_perlin	perlin;
	t_obj_wood		wood;
	t_obj_checker	checker;
	double			roughness;
	double			angle;
	double			radius;
	double			big_radius;
	double			bump;
	double			intensity;
	double			diffuse;
	double			specular;
	double			shininess;
	double			reflective;
	double			refractive;
	double			rf_factor;
	double			normal_circle;
	t_quaternion	rot_quat;
	t_quaternion	inv_rot_quat;
};

void				get_plane_dist(t_ray_object *object, t_ray_hit *hit);
void				get_cone_dist(t_ray_object *object, t_ray_hit *hit);
void				get_torus_dist(t_ray_object *object, t_ray_hit *hit);
void				get_sphere_dist(t_ray_object *object, t_ray_hit *hit);
void				get_cylinder_dist(t_ray_object *object, t_ray_hit *hit);
void				get_triangle_dist(t_ray_object *object, t_ray_hit *hit);
void				get_ellipsoid_dist(t_ray_object *object, t_ray_hit *hit);
void				get_hyperboloid_dist(t_ray_object *object, t_ray_hit *hit);
void				get_tanglecube_dist(t_ray_object *object, t_ray_hit *hit);

#endif
