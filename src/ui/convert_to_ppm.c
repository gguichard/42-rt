/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_ppm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:59:14 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/10 15:07:17 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include "libft.h"
#include "raytracer.h"

static int	create_name_screen(char name[30])
{
	time_t	actual_time;

	time(&actual_time);
	if (!(ctime_r(&actual_time, name)))
		return (1);
	name[24] = 0;
	ft_strcat(name, ".ppm");
	return (0);
}

static void	fill_ppm_file(unsigned int *view, int fd, t_data *data)
{
	int				i;
	int				j;
	unsigned char	color[3];

	i = 0;
	while (i < data->winsize.height)
	{
		j = 0;
		while (j < data->winsize.width)
		{
			color[0] = (view[i * data->winsize.width + j] >> 16) % 256;
			color[1] = (view[i * data->winsize.width + j] >> 8) % 256;
			color[2] = (view[i * data->winsize.width + j]) % 256;
			ft_dprintf(fd, "%3d %3d %3d  ", color[0], color[1], color[2]);
			j++;
		}
		ft_dprintf(fd, "\n");
		i++;
	}
}

int			convert_to_ppm(unsigned int *view, t_data *data)
{
	int		fd;
	char	name[30];

	ft_memset(&name, 0, sizeof(name));
	if (create_name_screen(name))
		return (1);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	ft_dprintf(fd, "P3\n%d %d\n255\n", data->winsize.width
		, data->winsize.height);
	fill_ppm_file(view, fd, data);
	close(fd);
	return (0);
}
