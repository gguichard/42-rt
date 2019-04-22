/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 06:06:51 by gguichar         ###   ########.fr       */
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

static void	init_threads(t_data *data)
{
	int	height_per_thread;
	int	y_offset;
	int	idx;

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

static void	init_camera(t_camera *camera)
{
	camera->fov = tan(90 * .5 / 180 * M_PI);
	camera->direction = vec3d_unit(camera->direction);
	camera->right = rotate_by_quaternion(camera->direction
			, (t_vec3d){0, 1, 0}, M_PI / 2);
	printf("%lf, %lf, %lf\n", camera->right.x, camera->right.y, camera->right.z);
	camera->up = rotate_by_quaternion(camera->right, camera->direction, M_PI / 2);
}

int			main(int argc, char **argv)
{
	t_data	data;
	t_error	err;

	if (argc < 2)
	{
		ft_dprintf(STDERR_FILENO, "%s: please specify a scene file\n", argv[0]);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	data.winsize.width = WIN_WIDTH;
	data.winsize.height = WIN_HEIGHT;
	data.winsize.aspect_ratio = data.winsize.width
		/ (double)data.winsize.height;
	err = parse_scene(&data, argv[1]);
	if (err == ERR_NOERROR)
	{
		init_threads(&data);
		data.square_pixels_per_ray = 5;
		init_camera(&data.camera);
		err = init_and_create_window(&data.lib, data.winsize);
	}
	if (err != ERR_NOERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s: error: %s\n", argv[0]
				, error_to_str(err));
		return (1);
	}
	run_event_loop(&data, trace_rays);
	destroy_lib(&data.lib);
	return (0);
}
