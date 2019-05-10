/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 04:49:00 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/10 17:23:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H

/*
** INCLUDES
*/

# include "SDL.h"
# include "ray_inf.h"
# include "ray_object.h"
# include "vec3d.h"

/*
** TYPEDEF & STRUCURES
*/

typedef struct s_data	t_data;

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

t_vec3d			apply_effects(t_data *data, t_ray_inf *ray_inf, t_vec3d color
	, t_vec3d init_color);

void			add_normal_perturbation(t_ray_inf *ray_inf);
t_vec3d			add_color_perturbation(t_ray_inf *ray_inf, t_vec3d base_color);

double			perlin_noise(t_vec3d intersect, int type);
void			perlin_random_permutation(t_perlin *perlin);
void			perlin_basic_permutation(t_perlin *perlin);
t_vec3d			perlin_noise_filter(t_vec3d intersect, t_vec3d color1
	, t_vec3d color2, t_vec3d color3);
t_vec3d			wood_filter(t_vec3d intersect, t_vec3d color1, t_vec3d color2);
t_vec3d			wavy_perturbation(t_vec3d normal, t_vec3d intersect);
t_vec3d			bump_mapping(t_vec3d normal, t_vec3d intersect, double bump
	, int type);

t_vec3d			apply_checkerboard(t_vec3d intersect, t_vec3d base_color
	, t_obj_checker board);
t_vec3d			apply_fog_effect(t_data *data, t_ray_inf *ray_inf
	, t_vec3d color);

t_vec3d			gray_filter(t_vec3d color);
t_vec3d			cartoon_filter(t_vec3d color, t_vec3d init_color);

void			filter_key_apply(SDL_Event *event, t_data *data);

#endif
