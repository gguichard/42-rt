/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:16:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/23 09:39:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_PARSER_H
# define MODEL_PARSER_H

typedef struct	t_wf_obj
{
	t_list			*vertices_list;
	t_vec3d			**vertices;
	t_wf_vertices	*vertices;
}

typedef struct	t_wf_vertices
{
	t_vec3d	vertex1;
	t_vec3d	vertex2;
	t_vec3d	vertex3;
}

#endif
