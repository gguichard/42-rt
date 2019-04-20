#include <math.h>

double		solve_quadratic_equation(double a, double b, double c)
{
	double	delta;
	double	sqrt_delta;
	double	result1;
	double	result2;

	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		a = 2 * a;
		sqrt_delta = sqrt(delta);
		result1 = (-b + sqrt_delta) / a;
		result2 = (delta == 0 ? result1 : (-b - sqrt_delta) / a);
		if (result1 >= 0 && result2 >= 0)
			return (result1 < result2 ? result1 : result2);
		else if (result1 >= 0)
			return (result1);
		else if (result2 >= 0)
			return (result2);
	}
	return (-1);
}
