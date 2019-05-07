/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kd_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 04:22:15 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/05 04:37:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KD_TREE_H
# define KD_TREE_H

# include "libft.h"
# include "vec3d.h"

typedef struct s_kd_tree	t_kd_tree;

struct						s_kd_tree
{
	t_vec3d					bbox_min;
	t_vec3d					bbox_max;
	t_vector				objects;
	t_kd_tree				*left;
	t_kd_tree				*right;
};

char						get_next_axis(char axis);
void						del_kd_tree(t_kd_tree *tree);

#endif
