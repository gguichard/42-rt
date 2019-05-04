/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:06:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 17:41:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "vec3d.h"

# define GAMMA_CORRECTION .45454545454

void			swap_f(double *ptr1, double *ptr2);
double			clamp(double value, double lo, double hi);
unsigned int	get_color_with_gamma_correction(t_vec3d color);

void			grow_bbox(t_vec3d *bbox_min, t_vec3d *bbox_max
	, t_vec3d *vertex);

#endif
