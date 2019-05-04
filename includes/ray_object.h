/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:42:39 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/04 02:21:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_OBJECT_H
# define RAY_OBJECT_H

# include "libft.h"
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
# define RAYOBJ_TRIANGLEMESH 10
# define RAYOBJ_LIGHT 11
# define RAYOBJ_AMBIENTLIGHT 12

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

typedef struct s_mesh_tree	t_mesh_tree;

typedef struct		s_triangle
{
	t_vec3d			vertices[3];
	t_vec3d			normals[3];
}					t_triangle;

struct				s_mesh_tree
{
	t_vec3d			bbox_min;
	t_vec3d			bbox_max;
	t_vector		triangles;
	t_mesh_tree		*left;
	t_mesh_tree		*right;
};

struct				s_ray_object
{
	int				type;
	void			(*hit_fn)(t_ray_object *, t_ray_hit *);
	t_mesh_tree		mesh_tree;
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

int					create_mesh_tree(t_mesh_tree *tree, char axis, int depth);

void				hit_plane(t_ray_object *object, t_ray_hit *hit);
void				hit_cone(t_ray_object *object, t_ray_hit *hit);
void				hit_torus(t_ray_object *object, t_ray_hit *hit);
void				hit_sphere(t_ray_object *object, t_ray_hit *hit);
void				hit_cylinder(t_ray_object *object, t_ray_hit *hit);
void				hit_triangle(t_ray_object *object, t_ray_hit *hit);
void				hit_ellipsoid(t_ray_object *object, t_ray_hit *hit);
void				hit_hyperboloid(t_ray_object *object, t_ray_hit *hit);
void				hit_tanglecube(t_ray_object *object, t_ray_hit *hit);
void				hit_trianglemesh(t_ray_object *object, t_ray_hit *hit);

#endif
