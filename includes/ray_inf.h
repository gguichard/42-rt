/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:08:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/20 23:57:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INF_H
# define RAY_INF_H

# include "vec3d.h"
# include "color.h"

typedef struct s_ray_object	t_ray_object;

typedef struct		s_ray_inf
{
	t_vec3d			origin;
	t_vec3d			direction;
	t_vec3d			intersect;
	t_vec3d			normal;
	t_ray_object	*object;
	t_color			color;
	double			dist;
}					t_ray_inf;

#endif
