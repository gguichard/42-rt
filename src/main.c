/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 00:32:47 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"
#include "parser.h"

static int	exit_with_error(t_error err, char *prog)
{
	ft_dprintf(STDERR_FILENO, "%s: error: %s\n", prog, error_to_str(err));
	return (1);
}

static void	init_winsize(t_data *data)
{
	data->winsize.width = WIN_WIDTH;
	data->winsize.height = WIN_HEIGHT;
	data->winsize.aspect_ratio = data->winsize.width
		/ (double)data->winsize.height;
}

int			main(int argc, char **argv)
{
	t_data	data;
	t_error	err;

	if (argc < 2)
		return (exit_with_error(ERR_NOSCENEFILE, argv[0]));
	ft_memset(&data, 0, sizeof(t_data));
	init_winsize(&data);
	err = parse_scene(&data, argv[1]);
	if (err == ERR_NOERROR)
		err = init_and_create_window(&data.lib, data.winsize);
	if (err != ERR_NOERROR)
		return (exit_with_error(err, argv[0]));
	data.sampling = 32;
	draw_panel(&data.lib);
	run_event_loop(&data);
	destroy_lib(&data.lib);
	ft_vecfree(&data.objects);
	ft_vecfree(&data.lights);
	return (0);
}
