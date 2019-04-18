/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:04:17 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/18 10:23:47 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

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

#endif
