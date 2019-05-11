/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:17:48 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:11:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "json_parser.h"
#include "raytracer.h"
#include "parser.h"
#include "error.h"

static char			*read_scene_file(const char *file_path, t_error *err)
{
	char	*str;
	int		fd;
	ssize_t	ret;
	char	buffer[4096];

	*err = err_noerror;
	str = NULL;
	if ((fd = open(file_path, O_RDONLY)) == -1)
		*err = err_errno;
	else
	{
		while ((ret = read(fd, &buffer, sizeof(buffer) - 1)) != 0)
		{
			buffer[ret] = '\0';
			if (ft_strlen(buffer) != (size_t)ret
				&& (*err = err_invalidscene) == err_invalidscene)
				break ;
			str = ft_strjoin_free(str, buffer);
		}
		if (ret == -1)
			*err = err_errno;
		close(fd);
	}
	return (*err != err_noerror ? ft_strdel(&str) : str);
}

static t_error		read_json_scene(t_data *data, t_json_token *root)
{
	t_error			err;
	t_json_token	*child;

	if (root->type != JSON_OBJECT)
		return (err_scenebadformat);
	else
	{
		err = err_noerror;
		child = root->value.child;
		while (err == err_noerror && child != NULL)
		{
			if (ft_strequ(child->key, "camera"))
				err = setup_camera_properties(data, child);
			else if (ft_strequ(child->key, "fog"))
				data->fog = read_json_double(child, &err);
			else if (ft_strequ(child->key, "objects"))
				err = parse_ray_objects(data, child);
			child = child->next;
		}
	}
	return (err);
}

static t_json_token	*decode_scene(t_data *data, const char *json_data
		, t_error *err)
{
	t_json_token	*root;

	*err = err_noerror;
	root = parse_json(json_data);
	if (root == NULL)
		*err = err_unexpected;
	else
	{
		*err = read_json_scene(data, root);
		del_json_token(root);
	}
	return (root);
}

t_error				parse_scene(t_data *data, const char *file_path)
{
	t_error	err;
	char	*scene_content;

	err = err_noerror;
	scene_content = read_scene_file(file_path, &err);
	if (err == err_noerror)
	{
		if (scene_content == NULL)
			err = err_invalidscene;
		else
		{
			decode_scene(data, scene_content, &err);
			free(scene_content);
		}
	}
	return (err);
}
