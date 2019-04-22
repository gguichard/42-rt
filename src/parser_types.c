#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "json_parser.h"
#include "parser.h"
#include "error.h"
#include "ray_object.h"

t_error	setup_camera_properties(t_data *data, t_json_token *token)
{
	t_error			err;
	t_json_token	*child;

	if (token->type != JSON_OBJECT)
		return (ERR_SCENEBADFORMAT);
	err = ERR_NOERROR;
	child = token->value.child;
	while (err == ERR_NOERROR && child != NULL)
	{
		if (ft_strequ(child->key, "origin"))
			data->camera.origin = read_json_vec3d(child, &err);
		else if (ft_strequ(child->key, "direction"))
			data->camera.direction = vec3d_unit(read_json_vec3d(child, &err));
		child = child->next;
	}
	return (err);
}

t_error	parse_ray_object_rotation(t_json_token *token, t_obj_rotation *rot)
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
			if (ft_strequ(child->key, "vector"))
				rot->vector = vec3d_unit(read_json_vec3d(child, &err));
			else if (ft_strequ(child->key, "angle"))
				rot->angle = read_json_double(child, &err) / 180. * M_PI;
			child = child->next;
		}
	}
	return (err);
}

t_error	parse_ray_object_vertices(t_json_token *token, t_vec3d *vertices)
{
	t_error			err;
	t_json_token	*child;
	int				idx;

	if (token->type != JSON_ARRAY)
		err = ERR_NOERROR;
	else
	{
		err = ERR_NOERROR;
		child = token->value.child;
		idx = 0;
		while (err == ERR_NOERROR && child != NULL && idx < 3)
		{
			vertices[idx] = read_json_vec3d(child, &err);
			child = child->next;
			idx++;
		}
		if (idx != 3 || child != NULL)
			err = ERR_SCENEBADFORMAT;
	}
	return (err);
}
