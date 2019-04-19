/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:11:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/19 09:54:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYOBJECT_H
# define RAYOBJECT_H

# include "vec3d.h"
# include "ray_inf.h"

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_LIGHT 2

typedef struct	s_ray_object
{
	int				type;
	t_vec3d			origin;
	t_vec3d			rotation;
	unsigned int	color;
	double			radius;
}				t_ray_object;

t_vec3d			get_intersect_normal(t_ray_inf *ray_inf, t_vec3d intersect);

double			get_sphere_intersect_dist(t_ray_object *object
		, t_ray_inf *ray_inf);

#endif
