/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:20:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:09:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"
#include "parser.h"
#include "error.h"

double	read_json_double(t_json_token *token, t_error *err)
{
	*err = err_noerror;
	if (token->type == JSON_FLOAT)
		return (token->value.f);
	else if (token->type == JSON_INTEGER)
		return ((double)token->value.i);
	else
	{
		*err = err_scenebadformat;
		return (0);
	}
}

int		read_json_boolean(t_json_token *token, t_error *err)
{
	int	value;

	value = 0;
	if (token->type != JSON_BOOLEAN)
		*err = err_scenebadformat;
	else
	{
		*err = err_noerror;
		value = token->value.i;
	}
	return (value);
}
