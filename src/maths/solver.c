/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:31:35 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/11 00:42:15 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "solver.h"
#include "vec3d.h"

void		solve_quadratic_equation(t_quad *quad)
{
	double	tmp;
	double	sqrt_delta;

	quad->delta = quad->b * quad->b - 4 * quad->a * quad->c;
	if (quad->delta < 0)
	{
		quad->t1 = -INFINITY;
		quad->t2 = -INFINITY;
	}
	else
	{
		tmp = quad->a * 2;
		sqrt_delta = sqrt(quad->delta);
		quad->t1 = (-quad->b + sqrt_delta) / tmp;
		quad->t2 = (quad->delta == 0
				? quad->t1 : (-quad->b - sqrt_delta) / tmp);
	}
}

static void	result_quartic_equation(t_quartic *quartic, t_vec3d tmp[8])
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
		tmp[7].x = -INFINITY;
		tmp[7].y = -INFINITY;
	}
	quartic->t1 = tmp[5].y;
	quartic->t2 = tmp[5].z;
	quartic->t3 = tmp[7].x;
	quartic->t4 = tmp[7].y;
}

static void	solve_quartic_equation2(t_quartic *quartic, t_vec3d tmp[8])
{
	tmp[3].x = tmp[0].y / 3.0 + tmp[2].z;
	tmp[3].y = sqrt(tmp[3].x - tmp[0].y);
	tmp[3].z = sqrt((tmp[3].x / 2.0) * (tmp[3].x / 2.0) - tmp[1].x);
	tmp[4].x = -(quartic->b / (4.0 * quartic->a));
	tmp[4].y = tmp[3].y * tmp[3].y - 2.0 * tmp[3].x - 4.0 * tmp[3].z;
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
		tmp[5].y = -INFINITY;
		tmp[5].z = -INFINITY;
	}
	tmp[6].x = tmp[3].y * tmp[3].y - 2.0 * tmp[3].x + 4.0 * tmp[3].z;
	result_quartic_equation(quartic, tmp);
}

void		solve_quartic_equation(t_quartic *quartic)
{
	t_vec3d	tmp[8];

	tmp[0].x = quartic->b / (2.0 * quartic->a);
	tmp[0].y = (quartic->c / quartic->a) - ((3.0 * tmp[0].x * tmp[0].x) / 2.0);
	tmp[0].z = (quartic->d / quartic->a) + pow(tmp[0].x, 3.0)
		- (quartic->c * tmp[0].x) / quartic->a;
	tmp[1].x = (quartic->e / quartic->a) - 3.0 * pow((tmp[0].x / 2.0), 4.0)
		+ (quartic->c / quartic->a) * (tmp[0].x / 2.0) * (tmp[0].x / 2.0)
		- (quartic->d / quartic->a) * (tmp[0].x / 2.0);
	tmp[1].y = -2.0 * pow((tmp[0].y / 3.0), 3.0) - tmp[0].z * tmp[0].z
		+ (8.0 / 3.0) * tmp[0].y * tmp[1].x;
	tmp[1].z = -(pow(tmp[0].y, 2.0) / 3.0) - 4.0 * tmp[1].x;
	tmp[2].x = pow((tmp[1].z / 3.0), 3.0) + (tmp[1].y / 2.0) * (tmp[1].y / 2.0);
	if (tmp[2].x > 0.0)
	{
		tmp[2].y = cbrt(-(tmp[1].y) / 2.0 + sqrt(tmp[2].x));
		tmp[2].z = tmp[2].y - tmp[1].z / 3.0 / tmp[2].y;
	}
	else if (tmp[2].x == 0.0)
		tmp[2].z = 3.0 * (tmp[1].y / tmp[1].z);
	else
		tmp[2].z = 2.0 * sqrt(-(tmp[1].z / 3.0)) * cos(1.0 / 3.0
				* acos(-(tmp[1].y / (2.0 * pow(-(tmp[1].z / 3.0)
								, 3.0 / 2.0)))));
	solve_quartic_equation2(quartic, tmp);
}
