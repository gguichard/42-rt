/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:13:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/23 17:14:44 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINSIZE_H
# define WINSIZE_H

# define WIN_TITLE "RTv1"
# define WIN_WIDTH 500
# define WIN_HEIGHT 500

typedef struct	s_winsize
{
	int			width;
	int			height;
	double		aspect_ratio;
}				t_winsize;

#endif
