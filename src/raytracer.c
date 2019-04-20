#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"
#include "color.h"

static int			trace_ray(t_data *data, t_ray_inf *ray_inf
		, int force_closest_object)
{
	t_list			*cur;
	t_ray_object	*obj;
	double			dist;

	cur = data->objects;
	while (cur != NULL)
	{
		obj = (t_ray_object *)cur->content;
		dist = -1;
		if (obj->type == RAYOBJ_SPHERE)
			dist = get_sphere_intersect_dist(obj, ray_inf);
		else if (obj->type == RAYOBJ_PLANE)
			dist = get_plane_intersect_dist(obj, ray_inf);
		if (dist >= .0)
		{
			if (!force_closest_object && dist < ray_inf->dist)
				return (1);
			if (force_closest_object
					&& (ray_inf->object == NULL || dist < ray_inf->dist))
			{
				ray_inf->object = obj;
				ray_inf->dist = dist;
			}
		}
		cur = cur->next;
	}
	return (force_closest_object && ray_inf->object != NULL);
}

static void			compute_light_color(t_data *data, t_ray_object *light
		, t_ray_inf *ray_inf, t_ray_inf *light_ray)
{
	double	angle;
	double	light_power;
	t_color	light_color;
	t_color	diffuse_color;

	if (light->type == RAYOBJ_AMBIENTLIGHT)
	{
		light_color = color_scale(light->color, light->intensity);
		ray_inf->color = color_add(ray_inf->color
				, color_mul(ray_inf->object->color, light_color));
	}
	else if (!trace_ray(data, light_ray, 0))
	{
		angle = vec3d_dot_product(light_ray->normal, light_ray->direction);
		if (angle >= .0)
		{
			light_power = angle * (light->intensity / pow(light_ray->dist, 2));
			light_color = color_scale(light->color, light_power);
			diffuse_color = color_mul(ray_inf->object->color, light_color);
			ray_inf->color = color_add(ray_inf->color, diffuse_color);
		}
	}
}

static void			trace_light_rays(t_data *data, t_ray_inf *ray_inf)
{
	t_vec3d			origin;
	t_ray_inf		light_ray;
	t_list			*cur;
	t_ray_object	*light;

	origin = vec3d_add(ray_inf->origin
			, vec3d_mul_by_scalar(ray_inf->direction, ray_inf->dist));
	light_ray.normal = get_intersect_normal(ray_inf, origin);
	light_ray.origin = vec3d_add(origin
			, vec3d_mul_by_scalar(light_ray.normal, 1e-4));
	cur = data->lights;
	while (cur != NULL)
	{
		light = (t_ray_object *)cur->content;
		light_ray.direction = vec3d_sub(light->origin, light_ray.origin);
		light_ray.dist = vec3d_length(light_ray.direction);
		light_ray.direction = vec3d_unit(light_ray.direction);
		compute_light_color(data, light, ray_inf, &light_ray);
		cur = cur->next;
	}
}

static t_ray_inf	trace_one_ray(t_data *data, t_vec3d ray_dir)
{
	t_ray_inf	ray_inf;

	ray_inf.origin = data->camera.origin;
	ray_inf.direction = ray_dir;
	ray_inf.color = (t_color){.0, .0, .0};
	ray_inf.object = NULL;
	if (trace_ray(data, &ray_inf, 1))
	{
		trace_light_rays(data, &ray_inf);
		ray_inf.color = color_clamp(ray_inf.color);
	}
	return (ray_inf);
}

static t_vec3d		get_ray_dir(t_data *data, int x, int y)
{
	t_vec3d	img_point;
	t_vec3d	ray_dir;

	img_point = vec3d_mul_by_scalar(data->camera.right
			, x / (double)data->winsize.width - .5);
	img_point = vec3d_sub(img_point
			, vec3d_mul_by_scalar(data->camera.up
				, y / (double)data->winsize.height - .5));
	img_point = vec3d_add(img_point, data->camera.origin);
	img_point = vec3d_add(img_point, data->camera.direction);
	ray_dir = vec3d_sub(img_point, data->camera.origin);
	return (vec3d_unit(ray_dir));
}

void				trace_rays(t_data *data)
{
	int			x;
	int			y;
	t_ray_inf	ray_inf;

	y = 0;
	while (y < data->winsize.height)
	{
		x = 0;
		while (x < data->winsize.width)
		{
			if (y % data->square_pixels_per_ray != 0)
				data->lib.view[y * data->winsize.width + x] =
					data->lib.view[(y - 1) * data->winsize.width + x];
			else
			{
				if (x % data->square_pixels_per_ray == 0)
					ray_inf = trace_one_ray(data, get_ray_dir(data, x, y));
				data->lib.view[y * data->winsize.width + x] =
					color_get_rgb(ray_inf.color);
			}
			x++;
		}
		y++;
	}
}
