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

/*double		solve_four_degrees_equation(t_vec3d abc, double d, double e)
{
	t_vec3d		tmp[5];

	tmp[0].x = pow(abc.x, 2);
	tmp[0].y = pow(abc.y, 2);
	tmp[0].z = pow(abc.z, 2);
	tmp[1].x = pow(d, 2);
	tmp[1].y = pow(e, 2);
	tmp[1].z = pow(abc.y, 3);
	tmp[2].x = pow(abc.z, 3);
	tmp[2].y = pow(d, 3);
	tmp[3].x = 256 * pow(abc.x, 3) * pow(e, 3) - 128 * tmp[0].x * tmp[1].y
		* tmp[0].z - 4 * pow(abc.y, 3) * pow(d, 3) + 16 abc.x * pow(abc.z, 4)
		* e - 4 * abc.x * tmp[2].x * tmp[1].x - 192 * tmp[0].x * abc.y * d
		* tmp[1].y - 27 * pow(abc.y, 4) * tmp[1].y - 6 * abc.x * tmp[0].y
		* tmp[1].x * e + 144 * abc.x * tmp[0].y * abc.z * tmp[1].y + 144
		* tmp[0].x * abc.z * tmp[1].x * e - 80 * abc.x * abc.y * tmp[0].z
		* d * e + 18 * tmp[1].z * abc.z * d * e + 18 * abc.x * abc.y * abc.z
		* tmp[2].y + tmp[0].y * tmp[0].z * tmp[1].x - 4 * tmp[0].y * tmp[2].x
		* e - 27 * tmp[0].x * pow(d, 4);
	tmp[3].y = 4 * (9 * tmp[0].y * tmp[0].z + 108 * abc.x * abc.y * abc.z * d
			- 108 * tmp[0].x * tmp[1].x + 32 * abc.x * tmp[2].x - 27
			* tmp[1].z * d);
	tmp[3].z = 12 * (3 * tmp[0].y - 8 * abc.x * abc.z);
	if (abc.a > 0 && tmp[3].y > 0)
	{
*/
