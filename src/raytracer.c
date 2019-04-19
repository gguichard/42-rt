/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:40:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/19 17:31:29 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"

static int		compute_light_color(int obj_color, int light_color
		, double percent)
{
	unsigned char	r[3];
	unsigned char	g[3];
	unsigned char	b[3];

	r[0] = (obj_color >> 16) & 0xFF;
	r[1] = (light_color >> 16) & 0xFF;
	r[2] = (r[1] - r[0]) * percent + r[0];
	g[0] = (obj_color >> 8) & 0xFF;
	g[1] = (light_color >> 8) & 0xFF;
	g[2] = (g[1] - g[0]) * percent + g[0];
	b[0] = obj_color & 0xFF;
	b[1] = light_color & 0xFF;
	b[2] = (b[1] - b[0]) * percent + b[0];
	return ((r[2] << 16) | (g[2] << 8) | b[2]);
}

static int		trace_ray(t_data *data, t_ray_inf *ray_inf, double max_dist
		, int force_closest_object)
{
	t_list			*cur;
	t_ray_object	*obj;
	double			dist;

	ray_inf->object = NULL;
	cur = data->objects;
	while (cur != NULL)
	{
		obj = (t_ray_object *)cur->content;
		dist = -1;
		if (obj->type == RAYOBJ_SPHERE)
			dist = get_sphere_intersect_dist(obj, ray_inf);
		if (dist > .0001 && dist <= max_dist && (dist < ray_inf->dist
					|| ray_inf->object == NULL))
		{
			ray_inf->object = obj;
			ray_inf->dist = dist;
			if (!force_closest_object)
				break ;
		}
		cur = cur->next;
	}
	return (ray_inf->object != NULL);
}

static void		trace_light_rays(t_data *data, t_ray_inf *ray_inf)
{
	t_ray_inf		light_ray;
	t_list			*cur;
	t_ray_object	*light;
	double			trace_max_dist;
	double			angle;

	light_ray.origin = vec3d_add(ray_inf->origin
			, vec3d_mul_by_scalar(ray_inf->direction, ray_inf->dist));
	light_ray.normal = get_intersect_normal(ray_inf, light_ray.origin);
	cur = data->lights;
	while (cur != NULL)
	{
		light = (t_ray_object *)cur->content;
		light_ray.direction = vec3d_sub(light->origin, light_ray.origin);
		trace_max_dist = vec3d_length(light_ray.direction);
		light_ray.direction = vec3d_unit(light_ray.direction);
		if (!trace_ray(data, &light_ray, trace_max_dist, 0))
		{
			angle = vec3d_dot_product(light_ray.normal, light_ray.direction);
			if (angle > 0.0)
				ray_inf->color = compute_light_color(ray_inf->color
						, light->color, angle);
		}
		cur = cur->next;
	}
}

static t_ray_inf	trace_one_ray(t_data *data, t_vec3d ray_dir)
{
	t_ray_inf		ray_inf;

	ray_inf.origin = data->camera.origin;
	ray_inf.direction = ray_dir;
	if (!trace_ray(data, &ray_inf, 9999.9, 1))
		ray_inf.color = 0x0;
	else
	{
		ray_inf.color = ray_inf.object->color;
		trace_light_rays(data, &ray_inf);
	}
	return (ray_inf);
}

static t_vec3d		get_ray_dir(t_data *data, int x, int y)
{
	t_vec3d	img_point;
	t_vec3d	ray_dir;

	img_point = vec3d_mul_by_scalar(data->camera.right
			, x / (double)data->winsize.width - 0.5);
	img_point = vec3d_sub(img_point
			, vec3d_mul_by_scalar(data->camera.up
				, y / (double)data->winsize.height - 0.5));
	img_point = vec3d_add(img_point, data->camera.origin);
	img_point = vec3d_add(img_point, data->camera.direction);
	ray_dir = vec3d_sub(img_point, data->camera.origin);
	return (vec3d_unit(ray_dir));
}

void				trace_rays(t_data *data)
{
	const int	skip_ratio = 2;
	int			x;
	int			y;
	t_ray_inf	ray_inf;

	y = 0;
	while (y < data->winsize.height)
	{
		x = 0;
		while (x < data->winsize.width)
		{
			if (y % skip_ratio != 0)
				data->lib.view[y * data->winsize.width + x] =
					data->lib.view[(y - 1) * data->winsize.width + x];
			else
			{
				if (x % skip_ratio == 0)
					ray_inf = trace_one_ray(data, get_ray_dir(data, x, y));
				data->lib.view[y * data->winsize.width + x] = ray_inf.color;
			}
			x++;
		}
		y++;
	}
}
