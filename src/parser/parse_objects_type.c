/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 17:54:33 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json_parser.h"
#include "parser.h"

static int	get_ray_light_type(t_json_token *token)
{
	if (token->type == JSON_STRING)
	{
		if (ft_strequ(token->value.str, "light"))
			return (RAYOBJ_LIGHT);
		else if (ft_strequ(token->value.str, "ambient_light"))
			return (RAYOBJ_AMBIENTLIGHT);
	}
	return (RAYOBJ_UNKNOWN);
}

static int	get_ray_object_type_2(t_json_token *token)
{
	if (ft_strequ(token->value.str, "csg_union"))
		return (RAYOBJ_CSGUNION);
	else if (ft_strequ(token->value.str, "csg_sub"))
		return (RAYOBJ_CSGSUB);
	else if (ft_strequ(token->value.str, "csg_inter"))
		return (RAYOBJ_CSGINTER);
	else if (ft_strequ(token->value.str, "trianglemesh"))
		return (RAYOBJ_TRIANGLEMESH);
	return (get_ray_light_type(token));
}

int			get_ray_object_type(t_json_token *token)
{
	if (token->type == JSON_STRING)
	{
		if (ft_strequ(token->value.str, "sphere"))
			return (RAYOBJ_SPHERE);
		else if (ft_strequ(token->value.str, "plane"))
			return (RAYOBJ_PLANE);
		else if (ft_strequ(token->value.str, "cylinder"))
			return (RAYOBJ_CYLINDER);
		else if (ft_strequ(token->value.str, "cone"))
			return (RAYOBJ_CONE);
		else if (ft_strequ(token->value.str, "torus"))
			return (RAYOBJ_TORUS);
		else if (ft_strequ(token->value.str, "triangle"))
			return (RAYOBJ_TRIANGLE);
		else if (ft_strequ(token->value.str, "ellipsoid"))
			return (RAYOBJ_ELLIPSOID);
		else if (ft_strequ(token->value.str, "hyperboloid"))
			return (RAYOBJ_HYPERBOLOID);
		else if (ft_strequ(token->value.str, "tanglecube"))
			return (RAYOBJ_TANGLECUBE);
		else
			return (get_ray_object_type_2(token));
	}
	return (get_ray_light_type(token));
}
