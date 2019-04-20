#ifndef SOLVER_H
# define SOLVER_H

/*
** TYPEDEF & STRUCTURES
*/

typedef struct	s_compute
{
	double		a;
	double		b;
	double		c;
	double		tmp1;
	double		tmp2;
	double		tmp3;
}				t_compute;

/*
** PROTOTYPES
*/

double			solve_quadratic_equation(double a, double b, double c);

#endif
