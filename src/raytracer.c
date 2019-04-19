/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:40:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/19 10:51:52 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "raytracer.h"
#include "ray_object.h"
#include "ray_inf.h"
#include "vec3d.h"

static t_ray_inf	trace_ray(t_data *data, t_vec3d ray_dir)
{
	t_ray_inf		ray_inf;
	t_list			*cur;
	t_ray_object	*obj;
	double			dist;

	ray_inf.object = NULL;
	cur = data->objects;
	while (cur != NULL)
	{
		obj = (t_ray_object *)cur->content;
		dist = -1;
		if (obj->type == RAYOBJ_SPHERE)
			dist = get_sphere_intersect(&data->camera, ray_dir, obj);
		if (dist >= 0 && (dist < ray_inf.dist || ray_inf.object == NULL))
		{
			ray_inf.object = obj;
			ray_inf.dist = dist;
		}
		cur = cur->next;
	}
	return (ray_inf);
}

static t_vec3d	get_ray_dir(t_data *data, int x, int y)
{
	t_vec3d	img_point;
	t_vec3d	ray_dir;

	img_point = vec3d_mul_by_scalar(data->camera.right
			, x / (double)data->winsize.width - 0.5);
	img_point = vec3d_add(img_point
			, vec3d_mul_by_scalar(data->camera.up
				, y / (double)data->winsize.height - 0.5));
	img_point = vec3d_add(img_point, data->camera.origin);
	img_point = vec3d_add(img_point, data->camera.direction);
	ray_dir = vec3d_sub(img_point, data->camera.origin);
	return (vec3d_unit(ray_dir));
}

void			trace_rays(t_data *data)
{
	const int	skip_ratio = 10;
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
					ray_inf = trace_ray(data, get_ray_dir(data, x, y));
				data->lib.view[y * data->winsize.width + x] =
					(ray_inf.object == NULL ? 0x0 : ray_inf.object->color);
			}
			x++;
		}
		y++;
	}
}
