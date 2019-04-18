/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayobject.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:11:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 10:00:42 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYOBJECT_H
# define RAYOBJECT_H

# define RAYOBJ_UNKNOWN 0
# define RAYOBJ_SPHERE 1
# define RAYOBJ_LIGHT 2

typedef struct	s_ray_object
{
	int			type;
	t_vec3d		origin;
	t_vec3d		rotation;
	void		*custom_data;
}				t_ray_object;

#endif
