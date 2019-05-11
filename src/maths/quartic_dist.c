/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quartic_dist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 00:41:47 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 00:42:11 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "solver.h"

static double	dist_min(double a, double b, double min_dist)
{
	if (a < min_dist && b < min_dist)
		return (-INFINITY);
	else if (b < min_dist)
		return (a);
	else if (a < min_dist)
		return (b);
	else
		return (a < b ? a : b);
}

double			get_quartic_min_dist(t_quartic *quartic, double min_dist)
{
	if (quartic->t1 < min_dist)
		quartic->t1 = -INFINITY;
	if (quartic->t2 < min_dist)
		quartic->t2 = -INFINITY;
	if (quartic->t3 < min_dist)
		quartic->t3 = -INFINITY;
	if (quartic->t4 < min_dist)
		quartic->t4 = -INFINITY;
	return (dist_min(quartic->t4, dist_min(quartic->t3, dist_min(quartic->t1
					, quartic->t2, min_dist), min_dist), min_dist));
}
