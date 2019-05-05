/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:27:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:29:00 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

void		infinity_mul(t_dconv *var, t_double *doub, int type)
{
	int			i;

	i = 0;
	ft_memset1(doub->real, 1, 10000);
	doub->real[10000] = 0;
	doub->i = 9999 - doub->exp - type;
	while (i < type)
	{
		doub->real[doub->i + i] = doub->mantisse[i];
		i++;
	}
	while (doub->i + i < 10000)
		doub->real[doub->i + i++] = '0';
	infinity_add(doub, var, type);
	var->str[0] = '.';
}

void		infinity_div(t_dconv *var, t_double *doub, int type)
{
	int			i;

	i = 0;
	ft_memset1(doub->real, 0, 10001);
	doub->i = 0;
	while (doub->i < -doub->exp)
		doub->real[doub->i++] = '0';
	while (i < type)
	{
		doub->real[doub->i + i] = doub->mantisse[i];
		i++;
	}
	infinity_add5(doub, var);
	var->str[0] = '.';
}

void		infinity_mul2(t_dconv *var, t_double *doub)
{
	int		ret;
	int		i;

	i = 9999;
	var->nbr = 0;
	while (doub->infinity[i] != 1)
	{
		ret = (var->nbr ? 1 : 0);
		var->nbr = 0;
		if (doub->infinity[i] >= '5')
		{
			var->nbr = (doub->infinity[i] - '0') * 2;
			doub->infinity[i] = var->nbr % 10 + '0';
		}
		else
			doub->infinity[i] = doub->infinity[i] * 2 - '0';
		if (ret)
			doub->infinity[i]++;
		i--;
	}
	if (var->nbr)
		doub->infinity[i] = '1';
}

void		infinity_div2(t_dconv *var, t_double *doub)
{
	int		ret;
	int		i;

	i = 0;
	var->nbr = 0;
	while (doub->infinity[i] != 1)
	{
		ret = (var->nbr ? 1 : 0);
		var->nbr = 0;
		if (doub->infinity[i] % 2 == 1)
			var->nbr = 1;
		doub->infinity[i] = (doub->infinity[i] - '0') / 2 + '0';
		if (ret)
			doub->infinity[i] += 5;
		i++;
	}
	if (var->nbr)
		doub->infinity[i] = '5';
}
