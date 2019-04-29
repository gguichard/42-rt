/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_ppm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:59:14 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/29 21:39:32 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <time.h>
#include "libft.h"
#include "lib.h"

static int	create_name_screen(char name[30])
{
	char	*time_clock;

	if (!(ctime_r(time(NULL), time_clock)))
		return (1);
	ft_strcpy(name, time_clock);
	ft_strcat(name, ".ppm");
	return (0);
}

int			convert_to_ppm(unsigned int *view, t_data *data)
{
	unsigned int	i;
	unsigned int	j;
	int				fd;
	char			name[30];
	unsigned char	color[3];

	ft_memset(&name, 0, 30);
	if (create_name_screen(name))
		return (1);
	fd = open(name, O_CREATE | O_WRONLY | O_TRUNC, 0644);
	if (fd <= 0)
		return (1);
	i = 0;
	ft_dprintf(fd, "P3\n%d %d\n255\n", data->winsize.width
		, data->winsize.heigth);
	while (i < data->winsize.heigth)
	{
		j = 0;
		while (j < data->winsize.width)
		{
			color[1] = view[i * data->winsize.heigth + j] >> 6 % 256;
			color[2] = view[i * data->winsize.heigth + j] >> 3 % 256;
			color[3] = view[i * data->winsize.heigth + j] % 256;
			ft_dprintf(fd, "%3d %3d %3d  ", color[1], color[2], color[3]);
			j++;
		}
		ft_dprintf(fd, "\n");
		i++;
	}
	return (0);
}
