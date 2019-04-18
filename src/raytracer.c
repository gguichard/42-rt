/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:40:53 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 14:54:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "raytracer.h"
#include "rayobject.h"
#include "vec3d.h"

/*
 *a = DIR.x^2 + DIR.y^2 + DIR.z^2
 b = 2 * (DIR.x * (O.x - Xc) + DIR.y * (O.y - Yc) + DIR.z * (O.z - Zc))
 c = ((O.x - Xc)^2 + (O.y - Yc)^2 + (O.z - Zc)^2) - r^2
 */

/*
 * t1 = (-b + sqrt(det)) / (2*a);
 * t2 = (-b - sqrt(det)) / (2*a);
 */

static void	launch_ray(t_data *data, int x, int y, t_vec3d ray_dir)
{
	t_list			*cur;
	t_ray_object	*obj;
	int				dist;

	cur = data->objects;
	dist = INT_MAX;
	while (cur != NULL)
	{
		obj = (t_ray_object *)cur->content;
		if (obj->type == RAYOBJ_SPHERE)
		{
			int radius = 2;
			double a = pow(ray_dir.x, 2) + pow(ray_dir.y, 2) + pow(ray_dir.z, 2);
			double b = 2 * (ray_dir.x * (data->camera.origin.x - obj->origin.x)
					+ ray_dir.y * (data->camera.origin.y - obj->origin.y)
					+ ray_dir.z * (data->camera.origin.z - obj->origin.z));
			double c = (pow(data->camera.origin.x - obj->origin.x, 2)
					+ pow(data->camera.origin.y - obj->origin.y, 2)
					+ pow(data->camera.origin.z - obj->origin.z, 2))
				- pow(radius, 2);
			double delta = pow(b, 2) - 4 * a * c;
			if (delta >= 0)
			{
				double t1 = (-b + sqrt(delta)) / (2 * a);
				double t2 = (-b - sqrt(delta)) / (2 * a);
				double t = t1 > t2 ? t2 : t1;
				if (t < 0)
					break ;
					//t = -t;
				data->lib.view[y * data->winsize.width + x] = 0xFFFFFFFF;
				return ;
			}
		}
		cur = cur->next;
	}
	data->lib.view[y * data->winsize.width + x] = 0x0;
}

static void	setup_camera(t_data *data)
{
	data->camera.right = vec3d_mul((t_vec3d){0, 1, 0}, data->camera.direction);
	data->camera.up = vec3d_mul(data->camera.direction, data->camera.right);
}

void		launch_rays(t_data *data)
{
	int		y;
	int		x;
	double	w;
	double	h;
	t_vec3d	img_point;
	t_vec3d	ray_dir;

	setup_camera(data);
	y = 0;
	while (y < data->winsize.height)
	{
		x = 0;
		while (x < data->winsize.width)
		{
			w = x / (double)data->winsize.width - 0.5;
			h = y / (double)data->winsize.height - 0.5;
			img_point = vec3d_mul_by_scalar(data->camera.right, w);
			img_point = vec3d_add(img_point
					, vec3d_mul_by_scalar(data->camera.up, h));
			img_point = vec3d_add(img_point, data->camera.origin);
			img_point = vec3d_add(img_point, data->camera.direction);
			ray_dir = vec3d_sub(img_point, data->camera.origin);
			ray_dir = vec3d_unit(ray_dir);
			launch_ray(data, x, y, ray_dir);
			x+=5;
		}
		y+=5;
	}
}
