/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:27:13 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:31:03 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

static int	end_fullish_conv(t_type *type, t_printf *data, char *format
	, va_list *ap)
{
	if (!(ft_strchr1(format[type->i], "CSPDIOUcspdiouxXfF%")))
		return (0);
	if (ft_strchr1(format[type->i], "CSPDIOU"))
		type->conv = format[type->i++] + 'a' - 'A';
	else
		type->conv = format[type->i++];
	send_to_buffer(type, data, ap);
	return (type->i);
}

static int	fullish_flag(t_type *type, t_printf *data, char *format
	, va_list *ap)
{
	while (ft_strchr1(format[type->i], "hlL"))
	{
		if (type->warning == 1)
			return (0);
		if (format[type->i] == 'h' && format[type->i + 1] == 'h'
			&& type->i++ > -1)
			type->hh = 1;
		else if (format[type->i] == 'h')
			type->h = 1;
		else if (format[type->i] == 'l' && format[type->i + 1] == 'l'
			&& type->i++ > -1)
			type->ll = 1;
		else if (format[type->i] == 'l')
			type->l = 1;
		else
			type->lmaj = 1;
		type->i++;
		type->warning++;
	}
	return (end_fullish_conv(type, data, format, ap));
}

static int	fullish_prec(t_type *type, t_printf *data, char *format
	, va_list *ap)
{
	if (format[type->i] == '.')
	{
		type->precision++;
		type->i++;
		if (format[type->i] == '*')
		{
			type->prec = va_arg(*ap, int);
			type->i++;
		}
		else
		{
			while (format[type->i] && format[type->i] >= '0'
				&& format[type->i] <= '9')
			{
				type->prec = type->prec * 10 + format[type->i] - '0';
				if (type->prec > 2147483647)
					return (free_error(type));
				type->i++;
			}
		}
	}
	return (fullish_flag(type, data, format, ap));
}

static int	fullish_width(t_type *type, t_printf *data, char *format
	, va_list *ap)
{
	if (format[type->i] == '*')
	{
		type->width = va_arg(*ap, int);
		type->i++;
	}
	else
	{
		while (format[type->i] && format[type->i] >= '0'
			&& format[type->i] <= '9')
		{
			type->width = type->width * 10 + format[type->i] - '0';
			if (type->width > 2147483647)
				return (0);
			type->i++;
		}
	}
	return (fullish_prec(type, data, format, ap));
}

int			start_fullish_attr(t_printf *data, char *format, va_list *ap)
{
	t_type		type;

	ft_memset1(&type, 0, sizeof(t_type));
	while (format[type.i] && ft_strchr1(format[type.i], " #+-0"))
	{
		if (format[type.i] == ' ' && !type.plus)
			type.space++;
		else if (format[type.i] == '#')
			type.sharp++;
		else if (format[type.i] == '+')
		{
			type.plus++;
			type.space = 0;
		}
		else if (format[type.i] == '-')
		{
			type.neg++;
			type.zero = 0;
		}
		else if (format[type.i] == '0' && !type.neg)
			type.zero++;
		type.i++;
	}
	return (fullish_width(&type, data, format, ap));
}
