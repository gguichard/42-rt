/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:49:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/05 19:20:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "wf_obj_parser.h"
#include "vec3d.h"
#include "error.h"

t_vec3d	*parse_wf_obj_vertex(char **split, t_error *err)
{
	t_vec3d	*vertex;

	vertex = NULL;
	if (ft_strtab_count(split) < 4)
		*err = ERR_BADOBJFILE;
	else
	{
		*err = ERR_NOERROR;
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

void	wf_add_vertex_to_vector(t_vector *vector, char **split, double scale
	, t_error *err)
{
	t_vec3d	*vertex;

	*err = ERR_NOERROR;
	vertex = parse_wf_obj_vertex(split, err);
	if (scale == 0)
		scale = 1 / vec3d_length(*vertex);
	*vertex = vec3d_scalar(*vertex, scale);
	if (*err == ERR_NOERROR && !ft_vecpush(vector, vertex))
	{
		free(vertex);
		*err = ERR_UNEXPECTED;
	}
}

void	free_wf_obj(t_wf_obj *obj)
{
	ft_vecdel(&obj->vertices, NULL);
	ft_vecdel(&obj->normals, NULL);
	ft_vecfree(&obj->tmp_vertices);
	ft_vecfree(&obj->tmp_normals);
}
