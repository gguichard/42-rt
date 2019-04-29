/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:06:11 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/29 21:00:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "vec3d.h"

# define GAMMA_CORRECTION .45454545454

double			clamp(double value, double lo, double hi);
unsigned int	get_color_with_gamma_correction(t_vec3d color);

#endif
