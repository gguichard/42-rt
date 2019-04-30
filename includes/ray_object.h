/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:42:39 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/30 23:40:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_OBJECT_H
# define RAY_OBJECT_H

# include "vec3d.h"
# include "ray_inf.h"
# include "quaternion.h"

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

typedef struct		s_obj_rotation
{
	t_vec3d			vector;
	double			angle;
}					t_obj_rotation;

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

struct				s_ray_object
{
	int				type;
	double			(*intersect)(t_ray_object *, t_vec3d, t_vec3d);
	t_vec3d			(*normal)(t_ray_object *, t_vec3d);
	t_vec3d			origin;
	t_vec3d			vertices[3];
	t_vec3d			size;
	t_vec3d			color;
	t_obj_perlin	perlin;
	t_obj_wood		wood;
	t_obj_rotation	rotation;
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
	t_quaternion	quat_rotate;
	t_quaternion	quat_invert_rotate;
};

void				assign_object_functions(t_ray_object *object);

double				get_plane_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_cone_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_torus_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_sphere_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_cylinder_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_triangle_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_ellipsoid_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_hyperboloid_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);
double				get_tanglecube_dist(t_ray_object *object
		, t_vec3d origin, t_vec3d direction);

t_vec3d				get_sphere_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_plane_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_cone_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_cylinder_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_torus_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_triangle_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_ellipsoid_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_hyperboloid_normal(t_ray_object *object
		, t_vec3d intersect);
t_vec3d				get_tanglecube_normal(t_ray_object *object
		, t_vec3d intersect);

#endif
