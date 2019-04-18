/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:40:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 15:57:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "raytracer.h"
#include "rayobject.h"
#include "vec3d.h"

static unsigned int	launch_ray(t_data *data, t_vec3d ray_dir)
{
	t_list			*cur;
	t_ray_object	*obj;
	int				dist;
	double			intersect;

	cur = data->objects;
	dist = INT_MAX;
	intersect = -1;
	while (cur != NULL)
	{
		obj = (t_ray_object *)cur->content;
		if (obj->type == RAYOBJ_SPHERE)
			intersect = get_sphere_intersect(&data->camera, ray_dir, obj);
		if (intersect >= 0)
			break ;
		cur = cur->next;
	}
	return (intersect >= 0 ? 0xFFFFFF : 0x0);
}

static t_vec3d	get_ray_dir(t_data *data, int x, int y)
{
	double	w;
	double	h;
	t_vec3d	img_point;
	t_vec3d	ray_dir;

	w = x / (double)data->winsize.width - 0.5;
	h = y / (double)data->winsize.height - 0.5;
	img_point = vec3d_mul_by_scalar(data->camera.right, w);
	img_point = vec3d_add(img_point
			, vec3d_mul_by_scalar(data->camera.up, h));
	img_point = vec3d_add(img_point, data->camera.origin);
	img_point = vec3d_add(img_point, data->camera.direction);
	ray_dir = vec3d_sub(img_point, data->camera.origin);
	return (vec3d_unit(ray_dir));
}

void			launch_rays(t_data *data)
{
	int	x;
	int	y;
	int	color;
	int	ratio;

	ratio = 10;
	data->camera.right = vec3d_mul((t_vec3d){0, 1, 0}, data->camera.direction);
	data->camera.up = vec3d_mul(data->camera.direction, data->camera.right);
	y = 0;
	while (y < data->winsize.height)
	{
		x = 0;
		while (x < data->winsize.width)
		{
			if (y % ratio != 0)
				color = data->lib.view[(y - 1) * data->winsize.width + x];
			else if (x % ratio == 0)
				color = launch_ray(data, get_ray_dir(data, x, y));
			data->lib.view[y * data->winsize.width + x] = color;
			x++;
		}
		y++;
	}
}
