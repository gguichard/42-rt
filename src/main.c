/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/25 03:11:45 by gguichar         ###   ########.fr       */
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

static void	init_winsize(t_data *data)
{
	data->winsize.width = WIN_WIDTH;
	data->winsize.height = WIN_HEIGHT;
	data->winsize.aspect_ratio = data->winsize.width
		/ (double)data->winsize.height;
}

static void	init_data(t_data *data)
{
	int	idx;

	data->square_pixels_per_ray = 5;
	data->camera.fov = tan(90 * .5 / 180 * M_PI);
	data->camera.direction = vec3d_unit(data->camera.direction);
	if (data->camera.direction.x == 0 && data->camera.direction.z == 0)
		data->camera.right = (t_vec3d){0, 0, 1};
	else
		data->camera.right = rotate_by_quaternion(data->camera.direction
				, (t_vec3d){0, 1, 0}, M_PI / 2);
	data->camera.up = rotate_by_quaternion(data->camera.right
			, data->camera.direction, M_PI / 2);
	idx = 0;
	while (idx < MAX_THREADS)
	{
		data->threads[idx].id = idx;
		data->threads[idx].data = data;
		idx++;
	}
}

static void	create_rotate_quaternions(t_data *data)
{
	size_t			index;
	t_ray_object	*object;

	index = 0;
	while (index < data->objects.size)
	{
		object = (t_ray_object *)data->objects.data[index];
		object->quat_rotate = vec3d_to_rotate_quaternion(
				object->rotation.vector, -object->rotation.angle);
		object->quat_invert_rotate = vec3d_to_rotate_quaternion
			(object->rotation.vector, object->rotation.angle);
		index++;
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
	init_winsize(&data);
	err = parse_scene(&data, av[1]);
	if (err == ERR_NOERROR)
	{
		create_rotate_quaternions(&data);
		err = init_and_create_window(&data.lib, data.winsize);
	}
	if (err != ERR_NOERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s: error: %s\n", av[0], error_to_str(err));
		return (1);
	}
	init_data(&data);
	run_event_loop(&data, trace_rays);
	destroy_lib(&data.lib);
	ft_vecfree(&data.objects);
	ft_vecfree(&data.lights);
	return (0);
}
