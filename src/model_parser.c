/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:10:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/23 18:43:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "vec3d.h"

static t_list	*parse_wf_obj_vertices(t_wf_obj *obj, char **split
		, t_error *err)
{
	t_list	*elem;
	t_vec3d	vec;
	char	*split;

	elem = NULL;
	*err = ERR_NOERROR;
	if (ft_strtab_count(split) < 4)
		*err = ERR_BADOBJFILE;
	else
	{
		vec.x = ft_bad_atof(split[1]);
		vec.y = ft_bad_atof(split[2]);
		vec.z = ft_bad_atof(split[3]);
		elem = ft_lstnew(&vec, sizeof(t_vec3d));
		if (elem == NULL)
			*err = ERR_UNEXPECTED;
	}
	return (elem);
}

static t_error	parse_wf_obj_line(t_wf_obj *obj, const char *line)
{
	t_error	err;
	char	**split;
	t_list	*elem;

	err = ERR_NOERROR;
	split = ft_strsplit(line, ' ');
	if (split == NULL)
		return (ERR_UNEXPECTED);
	else if (ft_strequ(split[0], "v"))
	{
		elem = parse_wf_obj_file(obj, split, &err);
		if (elem != NULL)
			ft_lstadd(&obj->vertices_list, elem);
		if (err != ERR_NOERROR)
			ft_lstfree(&obj->vertices_list);
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
