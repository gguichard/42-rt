/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:13:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/20 19:09:26 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINSIZE_H
# define WINSIZE_H

# define WIN_TITLE "RTv1"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

typedef struct	s_winsize
{
	int			width;
	int			height;
	double		aspect_ratio;
}				t_winsize;

#endif
