/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayobject.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:11:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 10:28:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYOBJECT_H
# define RAYOBJECT_H

# include "color.h"

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_LIGHT 2

typedef struct	s_ray_object
{
	int			type;
	t_vec3d		origin;
	t_vec3d		rotation;
	t_color		color;
}				t_ray_object;

#endif
