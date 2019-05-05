/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:49:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/05 06:04:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "wf_obj_parser.h"
#include "vec3d.h"
#include "error.h"

void	wf_add_vertex_to_vector(t_vector *vector, char **split, t_error *err)
{
	t_vec3d	*vertex;

	*err = ERR_NOERROR;
	vertex = parse_wf_obj_vertex(split, err);
	if (vertex != NULL && *err == ERR_NOERROR && !ft_vecpush(vector, vertex))
		*err = ERR_UNEXPECTED;
}

t_vec3d	*parse_wf_obj_vertex(char **split, t_error *err)
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

void	free_wf_obj(t_wf_obj *obj)
{
	ft_vecdel(&obj->vertices, NULL);
	ft_vecdel(&obj->normals, NULL);
	ft_vecfree(&obj->tmp_vertices);
	ft_vecfree(&obj->tmp_normals);
}
