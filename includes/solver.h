/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:42:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/02 13:30:59 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "vec3d.h"
# include "ray_object.h"

typedef struct	s_quad
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
}				t_quad;

typedef struct	s_quartic
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		tmp1;
	double		tmp2;
	double		tmp3;
}				t_quartic;

/*
** PROTOTYPES
*/

double			solve_quadratic_equation(t_quad *quad);
double			solve_quartic_equation(t_quartic *quartic);

double			add_limit_to_object(t_ray_object *object, t_quad quad
	, t_vec3d origin, t_vec3d direction);

#endif
