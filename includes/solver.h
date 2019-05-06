/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:42:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/06 07:51:52 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "vec3d.h"

typedef struct s_ray_hit	t_ray_hit;
typedef struct s_ray_object	t_ray_object;

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

double			add_limit_to_object(t_ray_object *object, double dist
	, t_ray_hit *hit);

#endif
