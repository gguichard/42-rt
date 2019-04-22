#include <stdlib.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_inf.h"
#include "ray_object.h"
#include "quaternion.h"
#include "vec3d.h"

t_vec3d	get_ray_dir(t_data *data, int x, int y)
{
	double	pixel_x;
	double	pixel_y;
	t_vec3d	dir;

	pixel_x = (2 * (x + .5) / data->winsize.width - 1) * data->camera.fov
		* data->winsize.aspect_ratio;
	pixel_y = (1 - (2 * (y + .5) / data->winsize.height)) * data->camera.fov;
	dir = vec3d_scalar(data->camera.right, pixel_x);
	dir = vec3d_add(dir, vec3d_scalar(data->camera.up, pixel_y));
	dir = vec3d_add(dir, data->camera.direction);
	return (vec3d_unit(dir));
}

int		has_object_in_ray(t_data *data, t_ray_inf *ray_inf
		, double max_dist_squared)
{
	t_list			*cur;
	t_ray_object	*obj;
	t_vec3d			origin;
	t_vec3d			direction;
	double			dist;

	cur = data->objects;
	while (cur != NULL)
	{
		obj = (t_ray_object *)cur->content;
		origin = vec3d_sub(ray_inf->origin, obj->origin);
		origin = rotate_by_quaternion(origin
				, obj->rotation.vector, -obj->rotation.angle);
		direction = rotate_by_quaternion(ray_inf->direction
				, obj->rotation.vector, -obj->rotation.angle);
		direction = vec3d_unit(direction);
		dist = get_intersect_dist(obj, origin, direction);
		if (dist > NEAR_PLANE_CLIPPING && (dist * dist) < max_dist_squared)
			return (1);
		cur = cur->next;
	}
	return (0);
}
