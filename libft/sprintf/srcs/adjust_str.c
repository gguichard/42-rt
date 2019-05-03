/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:27:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:27:21 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

static void	redo_str(t_dconv *var)
{
	ft_memmove1(var->str + 1, var->str, ft_strlen1(var->str) + 1);
	var->str[0] = '1';
}

static void	adjust_str3(t_type *type, t_dconv *var, int i)
{
	if (type->precision && type->prec > 0 && var->str[0] <= '9')
	{
		i += (type->prec < 10000 ? type->prec : 9999) + 1;
		var->nbr = var->str[i];
		var->str[i] = 0;
		if (var->nbr >= '5')
		{
			i--;
			while (i >= 0)
			{
				if (var->str[i] != '.')
				{
					var->str[i]++;
					if (var->str[i] > '9')
						var->str[i] = '0';
					else
						break ;
				}
				i--;
			}
			if (i == -1)
				redo_str(var);
		}
	}
}

static void	adjust_str2(t_type *type, t_dconv *var, int i)
{
	if (!type->precision || ((type->precision && type->prec < 0)
			&& var->str[0] <= '9'))
	{
		i += 7;
		var->nbr = var->str[i];
		var->str[i] = 0;
		if (var->nbr >= '5')
		{
			i--;
			while (i >= 0)
			{
				if (var->str[i] != '.')
				{
					if (++var->str[i] > '9')
						var->str[i] = '0';
					else
						break ;
				}
				i--;
			}
			if (i == -1)
				redo_str(var);
		}
	}
	adjust_str3(type, var, i);
}

void		rework_str(t_dconv *var, t_double *doub)
{
	int		j;

	doub->i = 0;
	while (var->str[doub->i] != 1 && var->str[doub->i])
	{
		doub->infinity[doub->i] = var->str[doub->i];
		doub->i++;
	}
	doub->infinity[doub->i] = 0;
	while (var->str[doub->i] == 1)
		doub->i++;
	j = 0;
	while (doub->i < 10000)
		doub->real[j++] = var->str[doub->i++];
	doub->real[j] = 0;
	doub->i = 0;
	j = 0;
	if (!doub->real[j] && doub->infinity[0] <= '9')
		var->str[doub->i++] = '0';
	while (doub->real[j])
		var->str[doub->i++] = doub->real[j++];
	j = 0;
	while (doub->infinity[j])
		var->str[doub->i++] = doub->infinity[j++];
	var->str[doub->i] = 0;
}

void		adjust_str(t_type *type, t_dconv *var)
{
	int		i;

	i = 0;
	while (var->str[i] != '.')
		i++;
	if (type->precision && !type->prec && var->str[0] <= '9')
	{
		var->str[i] = 0;
		if (var->str[i + 1] >= '5')
		{
			i--;
			while (i >= 0)
			{
				var->str[i]++;
				if (var->str[i] > '9')
					var->str[i] = '0';
				else
					break ;
				i--;
			}
			if (i == -1)
				redo_str(var);
		}
	}
	adjust_str2(type, var, i);
}
