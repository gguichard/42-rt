/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:14:29 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"
#include "parser.h"
#include "camera.h"
#include "ray_object.h"
#include "mesh_tree.h"

static int	exit_with_error(t_error err, char *prog)
{
	ft_dprintf(STDERR_FILENO, "%s: error: %s\n", prog, error_to_str(err));
	return (1);
}

static void	init_default_values(t_data *data)
{
	data->winsize.width = WIN_WIDTH;
	data->winsize.height = WIN_HEIGHT;
	data->winsize.aspect_ratio = data->winsize.width
		/ (double)data->winsize.height;
	data->camera.fov = tan(90 * .5 / 180 * M_PI);
}

int			main(int argc, char **argv)
{
	t_data	data;
	t_error	err;

	if (argc < 2)
		return (exit_with_error(err_noscenefile, argv[0]));
	ft_memset(&data, 0, sizeof(t_data));
	init_default_values(&data);
	err = parse_scene(&data, argv[1]);
	if (err == err_noerror)
		err = create_meshes_from_objects(&data.objects);
	if (err == err_noerror)
		err = init_and_create_window(&data.lib, data.winsize);
	if (err == err_noerror)
	{
		data.sampling = 32;
		init_camera(&data.camera);
		run_event_loop(&data);
	}
	destroy_lib(&data.lib);
	ft_vecdel(&data.objects, del_ray_object);
	ft_vecfree(&data.lights);
	if (err != err_noerror)
		return (exit_with_error(err, argv[0]));
	return (0);
}
