/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 05:27:04 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/22 05:37:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>
# include "vec3d.h"

# define MAX_THREADS 4

typedef struct s_thread	t_thread;

typedef struct	s_thread
{
	pthread_t	id;
	int			y_offset;
	int			height;
	t_data		*data;
}				t_thread;

#endif
