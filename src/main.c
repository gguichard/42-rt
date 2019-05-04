/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/04 20:34:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"
#include "parser.h"
#include "camera.h"

#include "ray_object.h"
#include "wf_obj_parser.h"
#include "math_utils.h"

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

static void	parse_wf_obj_file_degueux(t_data *data)
{
	t_error			err;
	t_wf_obj		wf_obj;
	size_t			idx;
	t_ray_object	*obj;
	t_triangle		*triangle;

	err = parse_wf_obj_file("file.obj", &wf_obj);
	if (err == ERR_NOERROR)
	{
		obj = ft_memalloc(sizeof(t_ray_object));
		obj->type = RAYOBJ_TRIANGLEMESH;
		obj->hit_fn = hit_trianglemesh;
		obj->color = (t_vec3d){1, 0.5, 0};
		obj->diffuse = 1.0;
		obj->rot_quat = xyz_rot_to_quat((t_vec3d){0, 0, 0});
		obj->inv_rot_quat = quaternion_conj(obj->rot_quat);
		idx = 0;
		while ((idx + 3) <= wf_obj.vertex_indices.size)
		{
			triangle = ft_memalloc(sizeof(t_triangle));
			triangle->vertices[0] =
				*((t_vec3d *)wf_obj.vertex_indices.data[idx]);
			triangle->vertices[1] =
				*((t_vec3d *)wf_obj.vertex_indices.data[idx + 1]);
			triangle->vertices[2] =
				*((t_vec3d *)wf_obj.vertex_indices.data[idx + 2]);
			triangle->normals[0] =
				*((t_vec3d *)wf_obj.normal_indices.data[idx]);
			triangle->normals[1] =
				*((t_vec3d *)wf_obj.normal_indices.data[idx + 1]);
			triangle->normals[2] =
				*((t_vec3d *)wf_obj.normal_indices.data[idx + 2]);
			ft_vecpush(&obj->mesh_tree.triangles, triangle);
			idx += 3;
		}
		ft_vecpush(&data->objects, obj);
		create_mesh_tree(&obj->mesh_tree, 'x', 0);
	}
}

int			main(int argc, char **argv)
{
	t_data	data;
	t_error	err;

	if (argc < 2)
		return (exit_with_error(ERR_NOSCENEFILE, argv[0]));
	ft_memset(&data, 0, sizeof(t_data));
	init_default_values(&data);
	err = parse_scene(&data, argv[1]);
	if (err == ERR_NOERROR)
		err = init_and_create_window(&data.lib, data.winsize);
	if (err == ERR_NOERROR)
	{
		parse_wf_obj_file_degueux(&data);
		data.sampling = 32;
		init_camera(&data.camera);
		run_event_loop(&data);
	}
	destroy_lib(&data.lib);
	ft_vecfree(&data.objects);
	ft_vecfree(&data.lights);
	if (err != ERR_NOERROR)
		return (exit_with_error(err, argv[0]));
	return (0);
}
