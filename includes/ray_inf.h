/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:08:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 19:16:13 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INF_H
# define RAY_INF_H

# include "ray_object.h"

typedef struct		s_ray_inf
{
	t_ray_object	*object;
	double			dist;
}					t_ray_inf;

#endif
