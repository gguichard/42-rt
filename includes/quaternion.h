/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:04:17 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/18 11:10:01 by roduquen         ###   ########.fr       */
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
	double		x;
	double		y;
	double		z;
	double		scalar;
}					t_quaternion;

/*
** PROTOTYPES
*/

double				quaternion_length(t_quaternion quat);
t_quaternion		quaternion_unit(t_quaternion quat);
t_quaternion		quaternion_mul(t_quaternion quat_a, t_quaternion quat_b);
t_quaternion		quaternion_conj(t_quaternion quat);
t_quaternion		vec3d_to_quaternion(t_vec3d vec, double angle);

#endif
