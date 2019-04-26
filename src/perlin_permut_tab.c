/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_permutation_tab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 05:13:19 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/26 11:06:33 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perturbations.h"
#include <stdlib.h>

void	perlin_permutation_tab(t_perlin *perlin)
{
	size_t	i;
	int		tmp;
	size_t	random;

	i = 0;
	while (i < 256)
	{
		perlin->permut[i] = i;
		i++;
	}
	i = 0;
	while (i < 256)
	{
		random = rand() % 256;
		tmp = perlin->permut[i];
		perlin->permut[i] = perlin->permut[random];
		perlin->permut[random] = tmp;
		i++;
	}
	while (i < 512)
	{
		perlin->permut[i] = perlin->permut[i - 256];
		i++;
	}
}
