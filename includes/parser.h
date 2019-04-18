/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:21:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/18 17:11:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "json_parser.h"
# include "raytracer.h"
# include "vec3d.h"

double			read_json_double(t_json_token *token, t_error *err);
t_vec3d			read_json_vec3d(t_json_token *token, t_error *err);
unsigned int	read_json_color(t_json_token *token, t_error *err);
t_error			setup_camera_properties(t_data *data, t_json_token *token);
t_error			parse_ray_objects(t_data *data, t_json_token *token);

t_error			parse_scene(t_data *data, const char *file_path);

#endif