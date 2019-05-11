/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:42:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/11 02:47:51 by gguichar         ###   ########.fr       */
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
	double		t1;
	double		t2;
	double		t3;
	double		t4;
}				t_quartic;

/*
** PROTOTYPES
*/

void			solve_quadratic_equation(t_quad *quad);
void			solve_quartic_equation(t_quartic *quartic);
double			get_quartic_min_dist(t_quartic *quartic, double min_dist);

int				has_object_limit(t_ray_object *object);
double			add_limit_to_object(t_ray_object *object, t_quad quad
	, t_ray_hit *hit);

#endif
