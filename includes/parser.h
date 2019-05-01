/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:21:38 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/01 12:35:36 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "json_parser.h"
# include "raytracer.h"
# include "ray_object.h"
# include "vec3d.h"
# include "error.h"

double			read_json_double(t_json_token *token, t_error *err);
t_vec3d			read_json_vec3d(t_json_token *token, t_error *err);
t_vec3d			read_json_color(t_json_token *token, t_error *err);
t_vec3d			parse_vec3d_rotation(t_json_token *token, t_error *err);

t_error			setup_camera_properties(t_data *data, t_json_token *token);
t_error			parse_ray_object_vertices(t_json_token *token
		, t_vec3d *vertices);
t_error			parse_ray_object_checker(t_json_token *token
		, t_obj_checker *board);

t_error			parse_ray_objects(t_data *data, t_json_token *token);
void			parse_object_property(t_json_token *child
		, t_ray_object *object, t_error *err);
int				get_ray_object_type(t_json_token *token);

t_error			parse_scene(t_data *data, const char *file_path);

#endif
