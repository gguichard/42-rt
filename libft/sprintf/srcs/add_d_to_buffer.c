/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_d_to_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:56:08 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:19:29 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include <stdlib.h>

static void	add_if_not_type_neg(t_type *type, t_printf *data, t_dconv *var)
{
	if (!type->neg && type->width >= 0)
	{
		if (var->nbr >= 0 && (type->space || type->plus) && !type->zero)
			ft_add_char_to_buff(data, (type->space ? ' ' : '+'));
		if (var->nbr < 0 && !type->zero)
			ft_add_char_to_buff(data, '-');
		while (var->prec-- > var->len)
			ft_add_char_to_buff(data, '0');
		while (--var->len >= 0)
		{
			if (!var->nbr && type->precision && !type->prec)
				ft_add_char_to_buff(data, ' ');
			else
				ft_add_char_to_buff(data, var->str[var->len]);
		}
	}
	free_time(var);
}

static void	add_width(t_type *type, t_printf *data, t_dconv *var)
{
	var->len = ft_strlen1(var->str);
	var->width -= (type->prec > var->len ? type->prec : var->len);
	if (type->plus || type->space || var->nbr < 0)
		var->width--;
	if (!type->neg && type->width >= 0 && type->zero)
	{
		if (var->nbr >= 0 && (type->space || type->plus))
			ft_add_char_to_buff(data, (type->space ? ' ' : '+'));
		if (var->nbr < 0)
			ft_add_char_to_buff(data, '-');
	}
	while (var->width-- > 0)
	{
		if (type->zero && !type->neg && type->width > 0 && !type->precision)
			ft_add_char_to_buff(data, '0');
		else
			ft_add_char_to_buff(data, ' ');
	}
	add_if_not_type_neg(type, data, var);
}

static void	add_if_type_neg(t_type *type, t_printf *data, t_dconv *var)
{
	if (type->neg || type->width < 0)
	{
		if (var->nbr >= 0 && (type->space || type->plus))
			ft_add_char_to_buff(data, (type->space ? ' ' : '+'));
		if (var->nbr < 0)
			ft_add_char_to_buff(data, '-');
		while (var->prec-- > var->len)
			ft_add_char_to_buff(data, '0');
		while (--var->len >= 0)
		{
			if (!var->nbr && type->precision && !type->prec)
				ft_add_char_to_buff(data, ' ');
			else
				ft_add_char_to_buff(data, var->str[var->len]);
		}
	}
	add_width(type, data, var);
}

int			add_d_to_buffer(t_type *type, t_printf *data, va_list *ap)
{
	t_dconv		*var;

	if (!(var = (t_dconv*)malloc(sizeof(t_dconv))))
		return (ERROR);
	ft_memset1(var, 0, sizeof(t_dconv));
	if (!type->warning)
		var->nbr = (int)va_arg(*ap, int);
	else if (type->hh)
		var->nbr = (char)va_arg(*ap, int);
	else if (type->h)
		var->nbr = (short int)va_arg(*ap, int);
	else if (type->l)
		var->nbr = (long int)va_arg(*ap, long int);
	else if (type->ll)
		var->nbr = (long long int)va_arg(*ap, long long int);
	if (type->precision && !type->prec && !type->width && var->nbr == 0)
		return (free_error(var));
	var->prec = type->prec;
	ft_ntoa(var);
	if (!var->str)
		return (free_error(var));
	var->len = ft_strlen1(var->str);
	var->width = (type->width < 0 ? -type->width : type->width);
	add_if_type_neg(type, data, var);
	return (0);
}
