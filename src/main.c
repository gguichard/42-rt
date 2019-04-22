/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 21:55:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include "SDL.h"
#include "libft.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"
#include "parser.h"
#include "ray_object.h"
#include "quaternion.h"

static void	init_data(t_data *data)
{
	int	height_per_thread;
	int	y_offset;
	int	idx;

	data->square_pixels_per_ray = 5;
	data->camera.fov = tan(90 * .5 / 180 * M_PI);
	data->camera.direction = vec3d_unit(data->camera.direction);
	data->camera.right = rotate_by_quaternion(data->camera.direction
			, (t_vec3d){0, 1, 0}, M_PI / 2);
	data->camera.up = rotate_by_quaternion(data->camera.right
			, data->camera.direction, M_PI / 2);
	height_per_thread = data->winsize.height / MAX_THREADS;
	y_offset = 0;
	idx = 0;
	while (idx < MAX_THREADS)
	{
		data->threads[idx].y_offset = y_offset;
		data->threads[idx].height = height_per_thread;
		data->threads[idx].data = data;
		y_offset += height_per_thread;
		idx++;
	}
}

int			main(int argc, char **av)
{
	t_data	data;
	t_error	err;

	if (argc < 2)
	{
		ft_dprintf(STDERR_FILENO, "%s: please specify a scene file\n", av[0]);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	data.winsize.width = WIN_WIDTH;
	data.winsize.height = WIN_HEIGHT;
	data.winsize.aspect_ratio = data.winsize.width
		/ (double)data.winsize.height;
	err = parse_scene(&data, av[1]);
	if (err == ERR_NOERROR)
		err = init_and_create_window(&data.lib, data.winsize);
	if (err != ERR_NOERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s: error: %s\n", av[0], error_to_str(err));
		return (1);
	}
	init_data(&data);
	run_event_loop(&data, trace_rays);
	destroy_lib(&data.lib);
	return (0);
}
