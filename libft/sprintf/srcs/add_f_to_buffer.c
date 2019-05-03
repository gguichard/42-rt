/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_f_to_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:21:18 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:20:09 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include <stdlib.h>

static void	add_if_not_type_neg(t_type *type, t_printf *data, t_dconv *var)
{
	if (!type->neg && type->width >= 0)
	{
		if ((type->precision && !type->prec) && type->sharp)
			ft_add_char_to_buff(data, '.');
		else if (var->str[var->nbr - 1] <= '9')
		{
			while (var->str[var->nbr])
			{
				var->prec--;
				ft_add_char_to_buff(data, var->str[var->nbr++]);
			}
			while (var->prec-- >= 0 && type->prec)
				ft_add_char_to_buff(data, '0');
		}
	}
	free_time(var);
}

static void	add_width(t_type *type, t_printf *data, t_dconv *var)
{
	while (var->width-- > 0)
	{
		if (type->zero && !type->neg && type->width > 0)
			data->buffer[data->actual++] = '0';
		else
			data->buffer[data->actual++] = ' ';
		if (data->actual == BUFF_SIZE)
			ft_putbuffer(data);
	}
	if (!type->neg && type->width >= 0)
	{
		if (var->str[0] != '-' && (type->space || type->plus) && !type->zero)
			ft_add_char_to_buff(data, (type->space ? ' ' : '+'));
		if (var->str[0] == '-' && !type->zero)
			ft_add_char_to_buff(data, '-');
		if (var->str[0] == '-')
			var->nbr++;
		while (var->str[var->nbr] != '.' && var->str[var->nbr])
			ft_add_char_to_buff(data, var->str[var->nbr++]);
	}
	add_if_not_type_neg(type, data, var);
}

static void	calcul_width(t_type *type, t_printf *data, t_dconv *var)
{
	int		i;

	i = 0;
	while (var->str[i] != '.' && var->str[i])
		i++;
	if (!type->neg && type->width >= 0 && type->zero)
	{
		if (var->str[0] != '-' && (type->space || type->plus))
			ft_add_char_to_buff(data, (type->space ? ' ' : '+'));
		if (var->str[0] == '-')
			ft_add_char_to_buff(data, '-');
	}
	var->width -= i + (var->str[1] <= '9' && var->str[0] != '-' ? 1 : 0);
	if (type->precision && !type->prec && type->sharp)
		var->width--;
	if (type->prec > 0 && var->str[1] <= '9')
		var->width -= type->prec;
	if (type->space || type->plus || var->str[0] == '-')
		var->width--;
	if (var->str[0] == '-' && var->str[1] > '9')
		var->width++;
	add_width(type, data, var);
}

static void	add_if_type_neg(t_type *type, t_printf *data, t_dconv *var)
{
	var->nbr = 0;
	if (type->neg || type->width < 0)
	{
		if (var->str[0] != '-' && (type->space || type->plus))
			ft_add_char_to_buff(data, (type->space ? ' ' : '+'));
		while (var->str[var->nbr] != '.' && var->str[var->nbr])
			ft_add_char_to_buff(data, var->str[var->nbr++]);
		if ((type->precision && !type->prec) && type->sharp)
			ft_add_char_to_buff(data, '.');
		else if (var->str[1] <= '9')
		{
			while (var->str[var->nbr])
			{
				var->prec--;
				ft_add_char_to_buff(data, var->str[var->nbr++]);
			}
			while (var->prec-- >= 0 && type->prec)
				ft_add_char_to_buff(data, '0');
		}
	}
	calcul_width(type, data, var);
}

int			add_f_to_buffer(t_type *type, t_printf *data, va_list *ap)
{
	t_dconv		*var;

	if (!(var = (t_dconv*)malloc(sizeof(t_dconv))))
		return (ERROR);
	ft_memset1(var, 0, sizeof(t_dconv));
	var->doub = (double)va_arg(*ap, double);
	double_calculator(var);
	var->prec = type->prec;
	if (!var->str)
		return (free_error(var));
	if (var->str[0] <= '9')
		adjust_str(type, var);
	else if (type->conv == 'F')
		ft_uppercase(var->str);
	if (var->nbr2 == 1)
	{
		ft_memmove1(var->str + 1, var->str, ft_strlen1(var->str) + 1);
		var->str[0] = '-';
	}
	var->width = (type->width < 0 ? -type->width : type->width);
	add_if_type_neg(type, data, var);
	return (0);
}
