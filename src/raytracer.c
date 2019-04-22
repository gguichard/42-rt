#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "thread.h"
#include "quaternion.h"
#include "vec3d.h"
#include "color.h"

static void			trace_ray(t_data *data, t_ray_inf *ray_inf)
{
	t_list			*cur;
	t_ray_object	*obj;
	double			dist;
	t_vec3d			origin;
	t_vec3d			direction;

	cur = data->objects;
	while (cur != NULL)
	{
		obj = (t_ray_object *)cur->content;
		world_to_object_transform(ray_inf, obj, &origin, &direction);
		dist = get_intersect_dist(obj, origin, direction);
		if (dist > NEAR_PLANE_CLIPPING
				&& (ray_inf->object == NULL || dist < ray_inf->dist))
		{
			ray_inf->object = obj;
			ray_inf->dist = dist;
			ray_inf->normal = get_intersect_normal(obj
					, vec3d_add(origin, vec3d_scalar(direction, dist)));
			ray_inf->normal = rotate_by_quaternion(ray_inf->normal
					, obj->rotation.vector, obj->rotation.angle);
		}
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
	trace_ray(data, &ray_inf);
	if (ray_inf.object != NULL)
	{
		ray_inf.intersect = vec3d_add(ray_inf.origin, vec3d_scalar(
					ray_inf.direction, ray_inf.dist));
		trace_light_rays(data, &ray_inf);
		ray_inf.color.r = pow(ray_inf.color.r, GAMMA_CORRECTION);
		ray_inf.color.g = pow(ray_inf.color.g, GAMMA_CORRECTION);
		ray_inf.color.b = pow(ray_inf.color.b, GAMMA_CORRECTION);
		ray_inf.color = color_clamp(ray_inf.color);
	}
	return (ray_inf);
}

static void			fill_ray_pixels(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->square_pixels_per_ray && (y + i) < data->winsize.height)
	{
		j = 0;
		while (j < data->square_pixels_per_ray && (x + j) < data->winsize.width)
		{
			data->lib.view[(y + i) * data->winsize.width + (x + j)] = color;
			j++;
		}
		i++;
	}
}

static void			*trace_rays_thread(t_thread *thread)
{
	t_data		*data;
	int			x;
	int			y;
	t_ray_inf	ray_inf;

	data = thread->data;
	y = thread->y_offset;
	while (y < thread->y_offset + thread->height)
	{
		if (y % data->square_pixels_per_ray != 0)
			y++;
		else
		{
			x = 0;
			while (x < data->winsize.width)
			{
				ray_inf = trace_one_ray(data, get_ray_dir(data, x, y));
				fill_ray_pixels(data, x, y, color_get_rgb(ray_inf.color));
				x += data->square_pixels_per_ray;
			}
			y += data->square_pixels_per_ray;
		}
	}
	return (NULL);
}

void				trace_rays(t_data *data)
{
	int	idx;

	idx = 0;
	while (idx < MAX_THREADS)
	{
		pthread_create(&data->threads[idx].id, NULL, (void *)trace_rays_thread
				, data->threads + idx);
		idx++;
	}
	idx = 0;
	while (idx < MAX_THREADS)
	{
		pthread_join(data->threads[idx].id, NULL);
		idx++;
	}
}
