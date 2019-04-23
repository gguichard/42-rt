/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:16:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/23 19:21:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_PARSER_H
# define MODEL_PARSER_H

# include "vec3d.h"

typedef struct		s_wf_obj
{
	t_vec3d			*vertices;
}					t_wf_obj;

typedef struct		s_wf_vertices
{
	t_vec3d			vertex1;
	t_vec3d			vertex2;
	t_vec3d			vertex3;
}					t_wf_vertices;

#endif
