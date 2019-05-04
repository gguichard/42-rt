/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:10:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/04 04:39:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "wf_obj_parser.h"
#include "vec3d.h"
#include "error.h"

static t_vec3d	*parse_wf_obj_vertex(char **split, t_error *err)
{
	t_vec3d	*vertex;

	vertex = NULL;
	*err = ERR_NOERROR;
	if (ft_strtab_count(split) < 4)
		*err = ERR_BADOBJFILE;
	else
	{
		vertex = (t_vec3d *)malloc(sizeof(t_vec3d));
		if (vertex == NULL)
			*err = ERR_UNEXPECTED;
		else
		{
			vertex->x = atof(split[1]);
			vertex->y = atof(split[2]);
			vertex->z = atof(split[3]);
		}
	}
	return (vertex);
}

static void		parse_wf_f_line_part(t_wf_obj *obj, const char *part
	, t_error *err)
{
	char	*endptr;
	size_t	vertex_indice;
	size_t	normal_indice;
	int		ret;

	*err = ERR_NOERROR;
	vertex_indice = ft_strtol(part, &endptr, 10);
	ret = 1;
	if (vertex_indice < 1 || vertex_indice > obj->vertices.size
		|| *endptr != '/')
		*err = ERR_BADOBJFILE;
	else
	{
		ft_strtol(endptr + 1, &endptr, 10);
		if (*endptr != '/')
			*err = ERR_BADOBJFILE;
		else
		{
			normal_indice = ft_strtol(endptr + 1, &endptr, 10);
			if ((*endptr != '\0' && *endptr != '/')
				|| normal_indice < 1 || normal_indice > obj->normals.size)
				*err = ERR_BADOBJFILE;
			else if (!ft_vecpush(&obj->normal_indices
					, obj->normals.data[normal_indice - 1])
				|| !ft_vecpush(&obj->vertex_indices
					, obj->vertices.data[vertex_indice - 1]))
				*err = ERR_UNEXPECTED;
		}
	}
}

static void		push_wf_obj_indices(t_wf_obj *obj, char **split, t_error *err)
{
	size_t	idx;

	if (ft_strtab_count(split) < 4)
		*err = ERR_BADOBJFILE;
	else
	{
		*err = ERR_NOERROR;
		idx = 0;
		while (*err == ERR_NOERROR && idx < 3)
		{
			parse_wf_f_line_part(obj, split[idx + 1], err);
			idx++;
		}
	}
}

static void		wf_add_vertex_to_vector(t_vector *vector, char **split
		, t_error *err)
{
	t_vec3d	*vertex;

	*err = ERR_NOERROR;
	vertex = parse_wf_obj_vertex(split, err);
	if (vertex != NULL && *err == ERR_NOERROR && !ft_vecpush(vector, vertex))
		*err = ERR_UNEXPECTED;
}

static t_error	parse_wf_obj_line(t_wf_obj *obj, const char *line)
{
	t_error	err;
	char	**split;

	err = ERR_NOERROR;
	split = ft_strsplit(line, ' ');
	if (split == NULL)
		return (ERR_UNEXPECTED);
	else if (ft_strequ(split[0], "f"))
		push_wf_obj_indices(obj, split, &err);
	else if (ft_strequ(split[0], "vn"))
		wf_add_vertex_to_vector(&obj->normals, split, &err);
	else if (ft_strequ(split[0], "v"))
		wf_add_vertex_to_vector(&obj->vertices, split, &err);
	if (err != ERR_NOERROR)
	{
		ft_vecfree(&obj->vertices);
		ft_vecfree(&obj->vertex_indices);
	}
	ft_strtab_free(split);
	return (err);
}

t_error			parse_wf_obj_file(const char *file, t_wf_obj *obj)
{
	int		fd;
	char	*line;
	int		ret;
	t_error	err;

	ft_memset(obj, 0, sizeof(t_wf_obj));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ERR_ERRNO);
	err = ERR_NOERROR;
	while (err == ERR_NOERROR && (ret = get_next_line(fd, &line)) == 1)
	{
		if (line[0] != '#')
			err = parse_wf_obj_line(obj, line);
		free(line);
	}
	if (ret != 0 && err == ERR_NOERROR)
		err = ERR_UNEXPECTED;
	close(fd);
	return (err);
}
