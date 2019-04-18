/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 19:24:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "SDL.h"
#include "libft.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"
#include "parser.h"
#include "ray_object.h"

static void	init_camera(t_camera *camera)
{
	camera->right = vec3d_cross_product((t_vec3d){0, 1, 0}, camera->direction);
	camera->up = vec3d_cross_product(camera->direction, camera->right);
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
	err = parse_scene(&data, argv[1]);
	if (err == ERR_NOERROR)
	{
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
