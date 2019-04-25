/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/25 19:25:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void		intersect_primary_ray(t_data *data, t_ray_inf *ray_inf)
{
	size_t			index;
	t_ray_object	*obj;
	double			dist;
	t_vec3d			origin;
	t_vec3d			direction;

	index = 0;
	while (index < data->objects.size)
	{
		obj = (t_ray_object *)data->objects.data[index];
		world_to_object_transform(ray_inf, obj, &origin, &direction);
		dist = obj->intersect(obj, origin, direction);
		if (dist > NEAR_PLANE_CLIPPING
				&& (ray_inf->object == NULL || dist < ray_inf->dist))
		{
			ray_inf->object = obj;
			ray_inf->dist = dist;
			ray_inf->normal = obj->normal(obj
					, vec3d_add(origin, vec3d_scalar(direction, dist)));
			ray_inf->normal = rotate_by_quaternion_with_quaternion(
					ray_inf->normal, obj->quat_invert_rotate);
		}
		index++;
	}
}

t_color			trace_primary_ray(t_data *data, t_vec3d origin, t_vec3d ray_dir
		, int depth)
{
	t_ray_inf	ray_inf;

	if (depth <= 0)
		return ((t_color){.0f, .0f, .0f});
	ray_inf.origin = origin;
	ray_inf.direction = ray_dir;
	ray_inf.color = (t_color){.0f, .0f, .0f};
	ray_inf.object = NULL;
	intersect_primary_ray(data, &ray_inf);
	if (ray_inf.object != NULL)
	{
		ray_inf.normal = vec3d_unit(ray_inf.normal);
		ray_inf.intersect = vec3d_add(ray_inf.origin
				, vec3d_scalar(ray_inf.direction, ray_inf.dist));
		if (ray_inf.object->mirror)
			return (trace_reflect_ray(data, &ray_inf, depth));
		else if (ray_inf.object->refractive != 0)
			return (trace_refract_ray(data, &ray_inf, depth));
		else
		{
			trace_light_rays(data, &ray_inf);
			ray_inf.color.r = pow(ray_inf.color.r, GAMMA_CORRECTION);
			ray_inf.color.g = pow(ray_inf.color.g, GAMMA_CORRECTION);
			ray_inf.color.b = pow(ray_inf.color.b, GAMMA_CORRECTION);
			ray_inf.color = color_clamp(ray_inf.color);
		}
	}
	return (ray_inf.color);
}

static void		fill_ray_pixels(t_data *data, int x, int y
		, unsigned int color)
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

static void		*trace_rays_thread(t_thread *thread)
{
	int				incr;
	int				x;
	int				y;
	unsigned int	color;

	incr = thread->data->square_pixels_per_ray * MAX_THREADS;
	y = thread->data->square_pixels_per_ray * thread->id;
	while (y < thread->data->winsize.height)
	{
		if (y % thread->data->square_pixels_per_ray != 0)
			y++;
		else
		{
			x = 0;
			while (x < thread->data->winsize.width)
			{
				color = color_to_rgb(trace_primary_ray(thread->data
						, thread->data->camera.origin
						, get_ray_dir(thread->data, x, y), 5));
				fill_ray_pixels(thread->data, x, y, color);
				x += thread->data->square_pixels_per_ray;
			}
			y += incr;
		}
	}
	return (NULL);
}

void			trace_rays(t_data *data)
{
	int	idx;

	idx = 0;
	while (idx < MAX_THREADS)
	{
		pthread_create(&data->threads[idx].pid, NULL, (void *)trace_rays_thread
				, data->threads + idx);
		idx++;
	}
	idx = 0;
	while (idx < MAX_THREADS)
	{
		pthread_join(data->threads[idx].pid, NULL);
		idx++;
	}
}
