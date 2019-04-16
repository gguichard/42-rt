/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:13:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/03/06 13:22:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINSIZE_H
# define WINSIZE_H

# define WIN_TITLE "Wolf3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

typedef struct	s_winsize
{
	int			width;
	int			height;
}				t_winsize;

#endif
