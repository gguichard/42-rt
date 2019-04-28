/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:10:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/27 19:36:20 by gguichar         ###   ########.fr       */
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
			vertex->x = ft_bad_atof(split[1]);
			vertex->y = ft_bad_atof(split[2]);
			vertex->z = ft_bad_atof(split[3]);
		}
	}
	return (vertex);
}

static void		push_wf_obj_indices(t_wf_obj *obj, char **split, t_error *err)
{
	size_t	v1;
	size_t	v2;
	size_t	v3;

	if (ft_strtab_count(split) < 4)
		*err = ERR_BADOBJFILE;
	else
	{
		*err = ERR_NOERROR;
		v1 = ft_atoi(split[1]) - 1;
		v2 = ft_atoi(split[2]) - 1;
		v3 = ft_atoi(split[3]) - 1;
		if (v1 >= obj->indices.size
				|| v2 >= obj->indices.size
				|| v3 >= obj->indices.size)
			*err = ERR_BADOBJFILE;
		else if (!ft_vecpush(&obj->indices, obj->vertices.data[v1])
				|| !ft_vecpush(&obj->indices, obj->vertices.data[v2])
				|| !ft_vecpush(&obj->indices, obj->vertices.data[v3]))
			*err = ERR_UNEXPECTED;
	}
}

static t_error	parse_wf_obj_line(t_wf_obj *obj, const char *line)
{
	t_error	err;
	char	**split;
	t_vec3d	*vertex;

	err = ERR_NOERROR;
	split = ft_strsplit(line, ' ');
	if (split == NULL)
		return (ERR_UNEXPECTED);
	else if (ft_strequ(split[0], "f"))
		push_wf_obj_indices(obj, split, &err);
	else if (ft_strequ(split[0], "v"))
	{
		vertex = parse_wf_obj_vertex(split, &err);
		if (vertex != NULL && err == ERR_NOERROR
				&& !ft_vecpush(&obj->vertices, vertex))
			err = ERR_UNEXPECTED;
	}
	if (err != ERR_NOERROR)
	{
		ft_vecfree(&obj->vertices);
		ft_vecfree(&obj->indices);
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