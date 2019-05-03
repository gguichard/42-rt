/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:27:06 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:03:26 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include <stdlib.h>

void		ft_ntoa(t_dconv *var)
{
	unsigned long long int	calc;
	int						i;
	int						size;

	i = 0;
	calc = (var->nbr < 0 ? -var->nbr : var->nbr);
	size = 1;
	while (calc > 0)
	{
		size++;
		calc /= 10;
	}
	if (!(var->str = (char*)malloc(sizeof(char) * (size + 2))))
		return ;
	calc = (var->nbr < 0 ? -var->nbr : var->nbr);
	while (calc > 0)
	{
		var->str[i++] = calc % 10 + '0';
		calc /= 10;
	}
	if (var->nbr == 0)
		var->str[i++] = '0';
	var->str[i] = 0;
}

void		ft_ntoa2(t_dconv *var)
{
	unsigned long long int	calc;
	int						i;
	int						size;

	i = 0;
	calc = var->nbr2;
	size = 1;
	while (calc > 0)
	{
		size++;
		calc /= 10;
	}
	if (!(var->str = (char*)malloc(sizeof(char) * (size + 2))))
		return ;
	calc = var->nbr2;
	while (calc > 0)
	{
		var->str[i++] = calc % 10 + '0';
		calc /= 10;
	}
	if (var->nbr2 == 0)
		var->str[i++] = '0';
	var->str[i] = 0;
}

void		ft_ntootoa(t_dconv *var)
{
	unsigned long long int	calc;
	int						i;
	int						size;

	i = 0;
	calc = var->nbr2;
	size = 1;
	while (calc > 0)
	{
		size++;
		calc /= 8;
	}
	if (!(var->str = (char*)malloc(sizeof(char) * (size + 2))))
		return ;
	calc = var->nbr2;
	while (calc > 0)
	{
		var->str[i++] = calc % 8 + '0';
		calc /= 8;
	}
	if (var->nbr2 == 0)
		var->str[i++] = '0';
	var->str[i] = 0;
}

void		ft_ntohtoa(t_dconv *var, char *base)
{
	unsigned long long int	calc;
	int						i;
	int						size;

	i = 0;
	calc = var->nbr2;
	size = 1;
	while (calc > 0)
	{
		size++;
		calc /= 16;
	}
	if (!(var->str = (char*)malloc(sizeof(char) * (size + 2))))
		return ;
	calc = var->nbr2;
	while (calc > 0)
	{
		var->str[i++] = base[calc % 16];
		calc /= 16;
	}
	if (var->nbr2 == 0)
		var->str[i++] = '0';
	var->str[i] = 0;
}
