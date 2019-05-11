/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:49:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:10:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "wf_obj_parser.h"
#include "vec3d.h"
#include "error.h"

static t_vec3d	*parse_wf_obj_vertex(char **split, t_error *err, double scale)
{
	t_vec3d	*vertex;

	vertex = NULL;
	if (ft_strtab_count(split) < 4)
		*err = err_badobjfile;
	else
	{
		*err = err_noerror;
		vertex = (t_vec3d *)malloc(sizeof(t_vec3d));
		if (vertex == NULL)
			*err = err_unexpected;
		else
		{
			vertex->x = atof(split[1]) * scale;
			vertex->y = atof(split[2]) * scale;
			vertex->z = atof(split[3]) * scale;
		}
	}
	return (vertex);
}

void			wf_add_vertex_to_vector(t_vector *vector, char **split
	, double scale, t_error *err)
{
	t_vec3d	*vertex;

	*err = err_noerror;
	vertex = parse_wf_obj_vertex(split, err, scale);
	if (*err == err_noerror && !ft_vecpush(vector, vertex))
	{
		free(vertex);
		*err = err_unexpected;
	}
}

void			free_wf_obj(t_wf_obj *obj)
{
	ft_vecdel(&obj->vertices, NULL);
	ft_vecdel(&obj->normals, NULL);
	ft_vecfree(&obj->tmp_vertices);
	ft_vecfree(&obj->tmp_normals);
}
