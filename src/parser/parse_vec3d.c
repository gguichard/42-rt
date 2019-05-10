/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:32:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 12:33:37 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "vec3d.h"
#include "error.h"

static int	write_json_vec3d_field(t_json_token **token, double *f)
{
	if (*token == NULL)
		return (0);
	if ((*token)->type != JSON_INTEGER && (*token)->type != JSON_FLOAT)
		return (0);
	*f = (*token)->type == JSON_FLOAT
		? (*token)->value.f
		: (double)(*token)->value.i;
	*token = (*token)->next;
	return (1);
}

t_vec3d		read_json_vec3d(t_json_token *token, t_error *err)
{
	t_vec3d			vec;
	t_json_token	*child;

	ft_memset(&vec, 0, sizeof(t_vec3d));
	if (token->type != JSON_ARRAY)
		*err = ERR_BADVEC3D;
	else
	{
		*err = ERR_NOERROR;
		child = token->value.child;
		if (!write_json_vec3d_field(&child, &vec.x)
			|| !write_json_vec3d_field(&child, &vec.y)
			|| !write_json_vec3d_field(&child, &vec.z)
			|| child != NULL)
			*err = ERR_BADVEC3D;
	}
	return (vec);
}
