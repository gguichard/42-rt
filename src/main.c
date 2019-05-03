/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 05:17:35 by gguichar         ###   ########.fr       */
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

static void	grow_bbox_min(t_vec3d *bbox, t_vec3d *vertex)
{
	if (vertex->x < bbox->x)
		bbox->x = vertex->x;
	if (vertex->y < bbox->y)
		bbox->y = vertex->y;
	if (vertex->z < bbox->z)
		bbox->z = vertex->z;
}

static void	grow_bbox_max(t_vec3d *bbox, t_vec3d *vertex)
{
	if (vertex->x > bbox->x)
		bbox->x = vertex->x;
	if (vertex->y > bbox->y)
		bbox->y = vertex->y;
	if (vertex->z > bbox->z)
		bbox->z = vertex->z;
}

static void	parse_wf_obj_file_degueux(t_data *data)
{
	t_error			err;
	t_wf_obj		wf_obj;
	size_t			idx;
	t_ray_object	*obj;
	t_vec3d			*vertices;

	err = parse_wf_obj_file("file.obj", &wf_obj);
	if (err == ERR_NOERROR)
	{
		obj = ft_memalloc(sizeof(t_ray_object));
		obj->type = RAYOBJ_TRIANGLEMESH;
		obj->hit_fn = hit_trianglemesh;
		obj->color = (t_vec3d){1, 1, 1};
		obj->diffuse = 1.0;
		obj->rot_quat = xyz_rot_to_quat((t_vec3d){0, 0, 0});
		obj->inv_rot_quat = quaternion_conj(obj->rot_quat);
		idx = 0;
		while (idx < wf_obj.indices.size)
		{
			vertices = ft_memalloc(sizeof(t_vec3d) * 3);
			vertices[0] = *((t_vec3d *)wf_obj.indices.data[idx]);
			vertices[1] = *((t_vec3d *)wf_obj.indices.data[idx + 1]);
			vertices[2] = *((t_vec3d *)wf_obj.indices.data[idx + 2]);
			grow_bbox_min(&obj->bbox_min, vertices);
			grow_bbox_min(&obj->bbox_min, vertices + 1);
			grow_bbox_min(&obj->bbox_min, vertices + 2);
			grow_bbox_max(&obj->bbox_max, vertices);
			grow_bbox_max(&obj->bbox_max, vertices + 1);
			grow_bbox_max(&obj->bbox_max, vertices + 2);
			ft_vecpush(&obj->triangles, vertices);
			idx += 3;
		}
		ft_vecpush(&data->objects, obj);
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
