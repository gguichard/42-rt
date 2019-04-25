/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wf_obj_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:16:59 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/25 05:37:32 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WF_OBJ_PARSER_H
# define WF_OBJ_PARSER_H

# include <string.h>
# include "libft.h"
# include "vec3d.h"
# include "error.h"

typedef struct		s_wf_obj
{
	t_vector		vertices;
	t_vector		indices;
}					t_wf_obj;

t_error				parse_wf_obj_file(const char *file, t_wf_obj *obj);

#endif