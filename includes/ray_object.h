#ifndef RAYOBJECT_H
# define RAYOBJECT_H

# include "vec3d.h"
# include "ray_inf.h"
# include "color.h"

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_LIGHT 2
# define RAYOBJ_AMBIENTLIGHT 3

typedef struct	s_ray_object
{
	int				type;
	t_vec3d			origin;
	t_vec3d			rotation;
	t_color			color;
	double			radius;
	double			intensity;
}				t_ray_object;

t_vec3d			get_intersect_normal(t_ray_inf *ray_inf, t_vec3d intersect);

double			get_plan_intersect_dist(t_ray_object *object
		, t_ray_inf *ray_inf);
double			get_sphere_intersect_dist(t_ray_object *object
		, t_ray_inf *ray_inf);

#endif
