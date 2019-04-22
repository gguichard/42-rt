#ifndef RAYOBJECT_H
# define RAYOBJECT_H

# include "vec3d.h"
# include "color.h"

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_PLANE 2
# define RAYOBJ_CYLINDER 3
# define RAYOBJ_CONE 4
# define RAYOBJ_LIGHT 5
# define RAYOBJ_AMBIENTLIGHT 6

typedef struct		s_obj_rotation
{
	t_vec3d			vector;
	double			angle;
}					t_obj_rotation;

typedef struct		s_ray_object
{
	int				type;
	t_vec3d			origin;
	t_color			color;
	t_obj_rotation	rotation;
	double			radius;
	double			intensity;
	double			specular;
	double			shininess;
	double			length;
}					t_ray_object;

double				get_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction);
t_vec3d				get_intersect_normal(t_ray_object *object
		, t_vec3d intersect);

#endif
