/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:56:35 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/21 03:22:09 by gguichar         ###   ########.fr       */
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

double			vec3d_length_squared(t_vec3d vec);
double			vec3d_length(t_vec3d vec);
t_vec3d			vec3d_unit(t_vec3d vec);
t_vec3d			vec3d_add(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_sub(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_cross_product(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d			vec3d_scalar(t_vec3d vec, double scalar);
double			vec3d_dot_product(t_vec3d vec_a, t_vec3d vec_b);

#endif
