/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:31:54 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:10:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "json_parser.h"
#include "parser.h"
#include "vec3d.h"
#include "math_utils.h"
#include "error.h"

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

t_vec3d		read_json_color(t_json_token *token, t_error *err)
{
	t_json_token	*child;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	t_vec3d			color;

	color = vec3d(0, 0, 0);
	if (token->type != JSON_ARRAY)
		*err = err_badcolor;
	else
	{
		*err = err_noerror;
		child = token->value.child;
		if (!write_json_color_field(&child, &r)
			|| !write_json_color_field(&child, &g)
			|| !write_json_color_field(&child, &b) || child != NULL)
			*err = err_badcolor;
		else
		{
			color.x = clamp(r / 255., 0, 1);
			color.y = clamp(g / 255., 0, 1);
			color.z = clamp(b / 255., 0, 1);
		}
	}
	return (color);
}
