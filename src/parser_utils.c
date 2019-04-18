/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:18:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 10:31:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "vec3d.h"
#include "color.h"

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

static int	write_json_color_field(t_json_token **token, unsigned char *i)
{
	if (*token == NULL)
		return (0);
	if ((*token)->type != JSON_INTEGER && (*token)->type != JSON_FLOAT)
		return (0);
	*i = (unsigned char)((*token)->type == JSON_INTEGER
		? (*token)->value.i
		: (*token)->value.f);
	*token = (*token)->next;
	return (1);
}

t_color		read_json_color(t_json_token *token, t_error *err)
{
	t_color			color;
	t_json_token	*child;

	ft_memset(&color, 0, sizeof(t_color));
	if (token->type != JSON_ARRAY)
		*err = ERR_BADCOLOR;
	else
	{
		*err = ERR_NOERROR;
		child = token->value.child;
		if (!write_json_color_field(&child, &color.r)
				|| !write_json_color_field(&child, &color.g)
				|| !write_json_color_field(&child, &color.b)
				|| child != NULL)
			*err = ERR_BADCOLOR;
	}
	return (color);
}
