#ifndef SOLVER_H
# define SOLVER_H

typedef struct	s_quad
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
}				t_quad;

/*
** PROTOTYPES
*/

double			solve_quadratic_equation(t_quad *quad);

#endif
