/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:04:17 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/01 04:04:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

/*
** INCLUDES
*/

# include "vec3d.h"

/*
** TYPEDEF & STRUCTURES
*/

typedef struct		s_quaternion
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_quaternion;

/*
** PROTOTYPES
*/

t_quaternion		quaternion_mul(t_quaternion quat_a, t_quaternion quat_b);
t_quaternion		quaternion_conj(t_quaternion quat);
t_quaternion		vec3d_to_rotate_quaternion(t_vec3d vec, double angle);

t_vec3d				rotate_by_quaternion_with_quaternion(t_vec3d vec
		, t_quaternion quat_rot_vec);
t_vec3d				rotate_by_quaternion(t_vec3d vec, t_vec3d rot_vec
		, double angle);
t_quaternion		xyz_rotation_to_quaternion(double x, double y, double z);

#endif
