#include <math.h>
#include "vec3d.h"
#include <stdio.h>

double			solve_quadratic_equation(double a, double b, double c)
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

static double	choose_min_positive(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	else if (a < 0)
		return (b);
	else if (b < 0)
		return (a);
	else
		return (a > b ? b : a);
}

static double	result_four_degrees_equation(t_vec3d tmp[8])
{
	if (tmp[0].z > 0.0)
		tmp[6].y = -(tmp[3].y / 2.0);
	else
		tmp[6].y = tmp[3].y / 2.0;
	tmp[6].z = sqrt(tmp[6].x < 0.0 ? -tmp[6].x : tmp[6].x) / 2.0;
	if (tmp[6].x >= 0)
	{
		tmp[7].x = tmp[6].y + tmp[4].x + tmp[6].z;
		tmp[7].y = tmp[6].y + tmp[4].x - tmp[6].z;
	}
	else
	{
		tmp[7].x = -1.0;
		tmp[7].y = -1.0;
	}
	return (choose_min_positive(tmp[5].y, choose_min_positive(tmp[5].z
					, choose_min_positive(tmp[7].x, tmp[7].y))));
}

static double	solve_four_degrees_equation2(t_vec3d abc, t_vec3d tmp[8])
{
	tmp[3].x = tmp[0].y / 3.0 + tmp[2].z;
	tmp[3].y = sqrt(tmp[3].x - tmp[0].y);
	tmp[3].z = sqrt(pow((tmp[3].x / 2.0), 2) - tmp[1].x);
	tmp[4].x = -(abc.y / (4.0 * abc.x));
	tmp[4].y = pow(tmp[3].y, 2.0) - 2.0 * tmp[3].x - 4.0 * tmp[3].z;
	if (tmp[0].z > 0.0)
		tmp[4].z = tmp[3].y / 2.0;
	else
		tmp[4].z = -(tmp[3].y / 2.0);
	tmp[5].x = sqrt(tmp[4].y < 0.0 ? -tmp[4].y : tmp[4].y) / 2.0;
	if (tmp[4].y >= 0)
	{
		tmp[5].y = tmp[4].z + tmp[4].x + tmp[5].x;
		tmp[5].z = tmp[4].z + tmp[4].x - tmp[5].x;
	}
	else
	{
		tmp[5].y = -1.0;
		tmp[5].z = -1.0;
	}
	tmp[6].x = pow(tmp[3].y, 2.0) - 2.0 * tmp[3].x + 4.0 * tmp[3].z;
	return (result_four_degrees_equation(tmp));
}

double			solve_four_degrees_equation(t_vec3d abc, double d, double e)
{
	t_vec3d			tmp[8];

	tmp[0].x = abc.y / (2.0 * abc.x);
	tmp[0].y = (abc.z / abc.x) - ((3.0 * pow(tmp[0].x, 2.0)) / 2.0);
	tmp[0].z = (d / abc.x) + pow(tmp[0].x, 3.0) - (abc.z * tmp[0].x) / abc.x;
	tmp[1].x = (e / abc.x) - 3.0 * pow((tmp[0].x / 2.0), 4.0) + (abc.z / abc.x)
		* pow((tmp[0].x / 2.0), 2.0) - (d / abc.x) * (tmp[0].x / 2.0);
	tmp[1].y = -2.0 * pow((tmp[0].y / 3.0), 3.0) - pow(tmp[0].z, 2.0)
		+ (8.0 / 3.0) * tmp[0].y * tmp[1].x;
	tmp[1].z = -(pow(tmp[0].y, 2.0) / 3.0) - 4.0 * tmp[1].x;
	tmp[2].x = pow((tmp[1].z / 3.0), 3.0) + pow((tmp[1].y / 2.0), 2.0);
	if (tmp[2].x > 0.0)
	{
		tmp[2].y = cbrt(-(tmp[1].y) / 2.0 + sqrt(tmp[2].x));
		tmp[2].z = tmp[2].y - tmp[1].z / 3.0 / tmp[2].y;
	}
	else if (tmp[2].x == 0.0)
		tmp[2].z = 3.0 * (tmp[1].y / tmp[1].z);
	else
		tmp[2].z = 2.0 * sqrt(-(tmp[1].z / 3.0)) * cos(1.0 / 3.0 * acos(-(tmp[1].y /
							(2.0 * pow(-(tmp[1].z / 3.0), 3.0 / 2.0)))));
	return (solve_four_degrees_equation2(abc, tmp));
}
