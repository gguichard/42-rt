/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kd_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 04:32:40 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/05 04:40:41 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "kd_tree.h"

char	get_next_axis(char axis)
{
	if (axis == 'x')
		return ('y');
	else if (axis == 'y')
		return ('z');
	else if (axis == 'z')
		return ('x');
	else
		return ('?');
}

void	del_kd_tree(t_kd_tree *tree)
{
	if (tree->left != NULL)
		del_kd_tree(tree->left);
	if (tree->right != NULL)
		del_kd_tree(tree->right);
	ft_vecfree(&tree->objects);
}
