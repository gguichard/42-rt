/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 04:49:00 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/26 16:10:08 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERTURBATIONS_H
# define PERTURBATIONS_H

/*
** INCLUDES
*/

# include "vec3d.h"

/*
** TYPEDEF & STRUCURES
*/

typedef struct	s_perlin
{
	int			permut[512];
	int			x;
	int			y;
	int			z;
	double		u;
	double		v;
	double		w;
	int			hash[6];
	double		result;
}				t_perlin;

/*
** PROTOTYPES
*/

double			perlin_noise(t_vec3d intersect);
void			perlin_random_permutation(t_perlin *perlin);
void			perlin_basic_permutation(t_perlin *perlin);
t_vec3d			normal_sin_perturbation(t_vec3d normal);
t_vec3d			uniform_bump_mapping(t_vec3d normal, double epsilon);
t_vec3d			plane_bump_mapping(t_vec3d normal, t_vec3d intersect
	, double epsilon);

#endif
