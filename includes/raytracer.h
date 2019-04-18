/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:56:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 11:46:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "SDL.h"
# include "libft.h"
# include "lib.h"
# include "winsize.h"
# include "camera.h"

typedef struct	s_data
{
	int			running;
	t_winsize	winsize;
	t_lib		lib;
	t_camera	camera;
	t_list		*objects;
}				t_data;

void			draw_view(t_data *data);
void			launch_rays(t_data *data);

#endif
