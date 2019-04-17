/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:11:26 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 14:20:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# define OBJ_UNKNOWN 0
# define OBJ_SPHERE 1
# define OBJ_LIGHT 2

typedef struct	s_object
{
	int			type;
	t_vec3d		pos;
	t_vec3d		rotation;
	void		*custom_data;
}				t_object;

#endif
