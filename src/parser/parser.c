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

	*err = ERR_NOERROR;
	str = NULL;
	if ((fd = open(file_path, O_RDONLY)) == -1)
		*err = ERR_ERRNO;
	else
	{
		while ((ret = read(fd, &buffer, sizeof(buffer) - 1)) != 0)
		{
			buffer[ret] = '\0';
			if (ft_strlen(buffer) != (size_t)ret
					&& (*err = ERR_INVALIDSCENE) == ERR_INVALIDSCENE)
				break ;
			str = ft_strjoin_free(str, buffer);
		}
		if (ret == -1)
			*err = ERR_ERRNO;
		close(fd);
	}
	return (*err != ERR_NOERROR ? ft_strdel(&str) : str);
}

static t_error		read_json_scene(t_data *data, t_json_token *root)
{
	t_error			err;
	t_json_token	*child;

	if (root->type != JSON_OBJECT)
		return (ERR_SCENEBADFORMAT);
	else
	{
		err = ERR_NOERROR;
		child = root->value.child;
		while (err == ERR_NOERROR && child != NULL)
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

	*err = ERR_NOERROR;
	root = parse_json(json_data);
	if (root == NULL)
		*err = ERR_UNEXPECTED;
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

	err = ERR_NOERROR;
	scene_content = read_scene_file(file_path, &err);
	if (err == ERR_NOERROR)
	{
		if (scene_content == NULL)
			err = ERR_INVALIDSCENE;
		else
		{
			decode_scene(data, scene_content, &err);
			free(scene_content);
		}
	}
	return (err);
}
