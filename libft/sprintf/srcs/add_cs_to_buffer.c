/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cs_to_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:55:24 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:18:33 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

static void	add_if_not_neg(t_type *type, t_printf *data, char *str, int i)
{
	while (type->sharp-- > 0 && str[i])
	{
		data->buffer[data->actual++] = str[i++];
		if (data->actual == BUFF_SIZE)
			ft_putbuffer(data);
	}
	if (i == 0 && !(type->precision && !type->prec))
	{
		while (str[i])
		{
			data->buffer[data->actual++] = str[i++];
			if (data->actual == BUFF_SIZE)
				ft_putbuffer(data);
		}
	}
}

static void	add_prec_and_width(t_type *type, t_printf *data, char *str, int i)
{
	int		len;

	len = ft_strlen1(str);
	if (type->precision)
	{
		if (type->prec < len)
			len = (type->prec >= 0 ? type->prec : ft_strlen1(str));
	}
	type->width = (type->width < 0 ? -type->width : type->width);
	while (type->width > len)
	{
		data->buffer[data->actual++] = ' ';
		type->width--;
		if (data->actual == BUFF_SIZE)
			ft_putbuffer(data);
	}
	if (i == 0)
		add_if_not_neg(type, data, str, i);
}

void		add_s_to_buffer(t_type *type, t_printf *data, va_list *ap)
{
	char	*str;
	int		i;

	type->sharp = type->prec;
	str = (char*)va_arg(*ap, char*);
	if (!str)
		str = "(null)";
	i = 0;
	if (type->neg || type->width < 0)
	{
		while (type->sharp - i > 0 && str[i])
			ft_add_char_to_buff(data, str[i++]);
		if (i == 0 && !(type->precision && !type->prec))
		{
			while (str[i])
				ft_add_char_to_buff(data, str[i++]);
		}
	}
	add_prec_and_width(type, data, str, i);
}

void		add_c_to_buffer(t_type *type, t_printf *data, va_list *ap)
{
	char	c;
	int		i;

	i = 0;
	c = (char)va_arg(*ap, int);
	if (type->neg || type->width < 0)
	{
		i++;
		ft_add_char_to_buff(data, c);
	}
	type->width = (type->width < 0 ? -type->width : type->width);
	while (type->width > 1)
	{
		ft_add_char_to_buff(data, ' ');
		type->width--;
	}
	if (i == 0)
		ft_add_char_to_buff(data, c);
}
