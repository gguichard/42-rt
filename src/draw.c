/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:41:48 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/09 17:31:19 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "raytracer.h"
#include "thread.h"
#include "vec3d.h"
#include "math_utils.h"

static void	draw_ray_sampling(t_data *data, int x, int y, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sampling && (y + i) < data->winsize.height)
	{
		j = 0;
		while (j < data->sampling && (x + j) < data->winsize.width)
		{
			data->lib.view[(y + i) * data->winsize.width + (x + j)] = color;
			j++;
		}
		i++;
	}
}

static void	draw_trace_ray(t_thread *thread, int x, int y)
{
	t_data	*data;
	t_vec3d	ray_dir;
	t_vec3d	color;

	data = thread->data;
	ray_dir = get_ray_dir(data, x, y);
	color = trace_primary_ray(data, data->camera.origin, ray_dir, 5);
	draw_ray_sampling(data, x, y, get_color_with_gamma_correction(color));
}

static void	*draw_trace_rays_thread(t_thread *thread)
{
	int	incr;
	int	x;
	int	y;

	incr = thread->data->sampling * MAX_THREADS;
	y = thread->data->sampling * thread->id;
	while (y < thread->data->winsize.height)
	{
		if (y % thread->data->sampling != 0)
			y++;
		else
		{
			x = 0;
			while (x < thread->data->winsize.width)
			{
				draw_trace_ray(thread, x, y);
				x += thread->data->sampling;
			}
			y += incr;
		}
	}
	return (NULL);
}

void		draw_trace_rays(t_data *data)
{
	int	idx;

	idx = 0;
	while (idx < MAX_THREADS)
	{
		data->threads[idx].id = idx;
		data->threads[idx].data = data;
		pthread_create(&data->threads[idx].pid, NULL
			, (void *)draw_trace_rays_thread, data->threads + idx);
		idx++;
	}
	idx = 0;
	while (idx < MAX_THREADS)
	{
		pthread_join(data->threads[idx].pid, NULL);
		idx++;
	}
}
