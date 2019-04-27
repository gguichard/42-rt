/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 04:49:00 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/27 05:42:15 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERTURBATIONS_H
# define PERTURBATIONS_H

/*
** INCLUDES
*/

# include "vec3d.h"
# include "ray_inf.h"

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

typedef struct	s_checkerboard
{
	t_vec3d		color;
	int			on;
}				t_checkerboard;

/*
** PROTOTYPES
*/

void			add_normal_perturbation(t_ray_inf *ray_inf);
t_vec3d			add_color_perturbation(t_ray_inf *ray_inf, t_vec3d color);

double			perlin_noise(t_vec3d intersect, int type);
void			perlin_random_permutation(t_perlin *perlin);
void			perlin_basic_permutation(t_perlin *perlin);
t_vec3d			normal_sin_perturbation(t_vec3d normal);
t_vec3d			bump_mapping(t_vec3d normal, t_vec3d intersect, double bump
	, int type);

t_vec3d			checkerboard(t_vec3d intersect, t_vec3d color1, t_vec3d color2);

#endif
