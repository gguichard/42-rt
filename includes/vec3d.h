/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:56:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 01:33:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

/*
** TYPEDEF & STRUCTURES
*/

typedef struct	s_vec3d
{
	double		x;
	double		y;
	double		z;
}				t_vec3d;

/*
** PROTOTYPES
*/

t_vec3d			vec3d(double x, double y, double z);
double			vec3d_length2(t_vec3d vec);
t_vec3d			vec3d_unit(t_vec3d vec);
t_vec3d			vec3d_add(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_sub(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_mul(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_cross(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_scalar(t_vec3d vec, double scalar);
double			vec3d_dot(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_reflect(t_vec3d direction, t_vec3d normal);

#endif
