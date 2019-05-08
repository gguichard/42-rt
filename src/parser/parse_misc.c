/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/08 12:47:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"
#include "parser.h"
#include "error.h"

double	read_json_double(t_json_token *token, t_error *err)
{
	*err = ERR_NOERROR;
	if (token->type == JSON_FLOAT)
		return (token->value.f);
	else if (token->type == JSON_INTEGER)
		return ((double)token->value.i);
	else
	{
		*err = ERR_SCENEBADFORMAT;
		return (0);
	}
}

int		read_json_boolean(t_json_token *token, t_error *err)
{
	int	value;

	value = 0;
	if (token->type != JSON_BOOLEAN)
		*err = ERR_SCENEBADFORMAT;
	else
	{
		*err = ERR_NOERROR;
		value = token->value.i;
	}
	return (value);
}
