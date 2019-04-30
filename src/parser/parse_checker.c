/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:08:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/30 17:11:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "ray_object.h"
#include "error.h"

t_error	parse_ray_object_checker(t_json_token *token, t_obj_checker *board)
{
	t_error			err;
	t_json_token	*child;

	if (token->type != JSON_OBJECT)
		err = ERR_SCENEBADFORMAT;
	else
	{
		err = ERR_NOERROR;
		child = token->value.child;
		while (err == ERR_NOERROR && child != NULL)
		{
			if (ft_strequ(child->key, "color"))
				board->color = read_json_color(child, &err);
			else if (ft_strequ(child->key, "size"))
				board->size = read_json_double(child, &err);
			child = child->next;
		}
	}
	return (err);
}
