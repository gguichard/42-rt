/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:13:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/10 15:38:29 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINSIZE_H
# define WINSIZE_H

# define WIN_TITLE "RT"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 860

typedef struct	s_winsize
{
	int			width;
	int			height;
	double		aspect_ratio;
}				t_winsize;

#endif
