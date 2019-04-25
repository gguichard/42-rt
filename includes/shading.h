/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:26:01 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/25 22:54:44 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H

typedef struct	s_shading
{
	double		eta;
	double		etai;
	double		etat;
	double		cosi;
	double		cost;
	double		sint;
	double		rs;
	double		rp;
}				t_shading;

#endif
