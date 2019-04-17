/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 22:56:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 12:10:28 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

# include "SDL.h"
# include "lib.h"
# include "winsize.h"

typedef struct	s_data
{
	int			running;
	t_winsize	winsize;
	t_lib		lib;
}				t_data;

void			draw_view(t_data *data);

#endif
