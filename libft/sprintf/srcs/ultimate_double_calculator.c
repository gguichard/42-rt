/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_double_calculator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:28:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/09 15:19:35 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include <stdlib.h>

static void	infinity_nan(t_dconv *var, t_double *doub, char *nan, char *inf)
{
	while (doub->i < 54)
	{
		if (doub->mantisse[doub->i] == '1')
			break ;
		doub->i++;
	}
	if (doub->i == 54)
	{
		doub->i = 0;
		while (inf[doub->i])
		{
			var->str[doub->i] = inf[doub->i];
			doub->i++;
		}
	}
	else
	{
		doub->i = 0;
		while (nan[doub->i])
		{
			var->str[doub->i] = nan[doub->i];
			doub->i++;
		}
	}
	var->str[doub->i] = 0;
}

static void	double_calculator2(t_dconv *var, t_double *doub)
{
	while (doub->i >= 0)
	{
		if (doub->exposant[doub->i])
			doub->exp += var->nbr2;
		var->nbr2 *= 2;
		doub->i--;
	}
	if (!(var->str = (char*)malloc(sizeof(char) * 10003)))
	{
		free(doub);
		return ;
	}
	ft_memset1(var->str, 0, 10001);
	doub->i = 1;
	if (var->doub == 0)
		zero_doub(var);
	else if (doub->exp == 1024)
		infinity_nan(var, doub, "nan.", "inf.");
	else if (doub->exp >= 0)
		infinity_mul(var, doub, 53);
	else
		infinity_div(var, doub, 53);
	if (var->doub != 0 && var->str[0] != '-' && var->str[0] <= '9')
		rework_str(var, doub);
}

static void	full_mantisse_exp(t_dconv *var, t_double *doub)
{
	while (var->nbr2 ^ 0)
	{
		if (doub->i == 0)
			doub->sign = (var->nbr2 & doub->coop ? '-' : '+');
		else if (doub->i < 12)
			doub->exposant[var->nbr++] = (var->nbr2 & doub->coop ? 1 : 0);
		else
		{
			if (doub->i == 12)
				var->nbr = 1;
			doub->mantisse[var->nbr++] = (var->nbr2 & doub->coop ? '1' : '0');
		}
		doub->i++;
		var->nbr2 /= 2;
	}
}

void		double_calculator(t_dconv *var)
{
	t_double	doub;

	ft_memset1(&doub, 0, sizeof(t_double));
	doub.coop = *((unsigned long long*)&(var->doub));
	var->nbr = 0;
	var->nbr2 = 4611686018427387904;
	var->nbr2 *= 2;
	doub.mantisse[0] = '1';
	full_mantisse_exp(var, &doub);
	doub.exp = -1023;
	var->nbr = (doub.sign == '-' ? 0 : 1);
	doub.i = 10;
	var->nbr2 = 1;
	double_calculator2(var, &doub);
	var->nbr2 = (doub.sign == '-' ? 1 : 0);
}

void		zero_doub(t_dconv *var)
{
	ft_memset1(var->str, '0', 10000);
	var->str[1] = '.';
	var->str[10000] = 0;
}
