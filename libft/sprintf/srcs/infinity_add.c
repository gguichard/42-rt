/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:27:48 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:30:10 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

static void	infinity_add2(t_double *doub, t_dconv *var, int i)
{
	int		ret;

	while (doub->infinity[i] != 1)
	{
		ret = (var->nbr >= 10 ? 1 : 0);
		if ((var->nbr = (var->str[i] != 1 ? var->str[i] - '0' : 0)
				+ doub->infinity[i] - '0') >= 10)
			var->str[i] = var->nbr % 10 + '0';
		else
			var->str[i] = var->nbr + '0';
		if (ret && var->str[i] != '9')
			var->str[i]++;
		else if (ret)
		{
			var->str[i] = '0';
			if (var->str[i - 1] != 1)
				var->str[i - 1]++;
			else
				var->str[i - 1] = '1';
		}
		i--;
	}
	if (var->nbr >= 10)
		var->str[i] = '1';
}

static void	infinity_add4(t_double *doub, t_dconv *var, int i)
{
	int		ret;

	while (i >= 0)
	{
		ret = (var->nbr >= 10 ? 1 : 0);
		if ((var->nbr = (var->str[i] != 1 ? var->str[i] - '0' : 0)
				+ doub->infinity[i] - '0') >= 10)
			var->str[i] = var->nbr % 10 + '0';
		else
			var->str[i] = var->nbr + '0';
		if (ret && var->str[i] != '9')
			var->str[i]++;
		else if (ret)
		{
			var->str[i] = '0';
			if (var->str[i - 1] != 1)
				var->str[i - 1]++;
			else
				var->str[i - 1] = '1';
		}
		i--;
	}
	if (var->nbr >= 10)
		var->str[i] = '1';
}

static void	infinity_add3(t_double *doub, t_dconv *var, int type)
{
	int		i;

	i = 0;
	ft_memset1(doub->infinity, 1, 10000);
	doub->infinity[10000] = 0;
	doub->infinity[0] = '1';
	ft_memset1(var->str, '0', 5000);
	doub->i = 9999 - type;
	while (doub->i < 10000)
	{
		var->nbr = 0;
		if (doub->i != 9999 - type && doub->real[doub->i] == '1')
		{
			i = 0;
			while (doub->infinity[i] != 1)
				i++;
			infinity_add4(doub, var, i - 1);
		}
		infinity_div2(var, doub);
		doub->i++;
	}
}

void		infinity_add(t_double *doub, t_dconv *var, int type)
{
	ft_memset1(doub->infinity, 1, 10000);
	doub->infinity[10000] = 0;
	doub->infinity[9999] = '1';
	ft_memset1(var->str, 1, 10000);
	var->str[10000] = 0;
	doub->i = 9999 - type;
	while (doub->real[doub->i] != 1)
	{
		var->nbr = 0;
		if (doub->real[doub->i] == '1')
			infinity_add2(doub, var, 9999);
		infinity_mul2(var, doub);
		doub->i--;
	}
	infinity_add3(doub, var, type);
}

void		infinity_add5(t_double *doub, t_dconv *var)
{
	int		i;

	i = 0;
	ft_memset1(doub->infinity, 1, 10000);
	doub->infinity[10000] = 0;
	doub->infinity[0] = '1';
	ft_memset1(var->str, '0', 5000);
	doub->i = 0;
	while (doub->real[doub->i] != 0)
	{
		var->nbr = 0;
		if (doub->i != 0 && doub->real[doub->i] == '1')
		{
			i = 0;
			while (doub->infinity[i] != 1)
				i++;
			infinity_add4(doub, var, i - 1);
		}
		infinity_div2(var, doub);
		doub->i++;
	}
}
