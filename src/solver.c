#include <math.h>
#include "solver.h"

double		solve_quadratic_equation(t_quad *quad)
{
	double	tmp;
	double	sqrt_delta;

	quad->delta = pow(quad->b, 2) - 4 * quad->a * quad->c;
	if (quad->delta >= 0)
	{
		tmp = quad->a * 2;
		sqrt_delta = sqrt(quad->delta);
		quad->t1 = (-quad->b + sqrt_delta) / tmp;
		quad->t2 = (quad->delta == 0
				? quad->t1 : (-quad->b - sqrt_delta) / tmp);
		if (quad->t1 >= 0 && quad->t2 >= 0)
			return (quad->t1 < quad->t2 ? quad->t1 : quad->t2);
		else if (quad->t1 >= 0)
			return (quad->t1);
		else if (quad->t2 > 0)
			return (quad->t2);
	}
	return (-1);
}
