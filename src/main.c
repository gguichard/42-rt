/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:55:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 13:11:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "SDL.h"
#include "libft.h"
#include "raytracer.h"
#include "error.h"
#include "lib.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_error	err;

	(void)argc;
	ft_memset(&data, 0, sizeof(t_data));
	data.winsize.width = WIN_WIDTH;
	data.winsize.height = WIN_HEIGHT;
	err = init_and_create_window(&data.lib, data.winsize);
	if (err != ERR_NOERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s: error: %s\n", argv[0]
				, error_to_str(err));
		return (1);
	}
	run_event_loop(&data, draw_view);
	destroy_lib(&data.lib);
	return (0);
}
