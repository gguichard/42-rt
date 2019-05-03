/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 13:51:11 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:28:34 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include <stdlib.h>

static void	detect_escape_char(const char *format, t_printf *data, va_list *ap)
{
	int			i;
	int			ret;

	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			ft_add_char_to_buff(data, format[i++]);
		else
		{
			i++;
			if ((ret = start_fullish_attr(data, (char*)format + i, ap))
				!= ERROR)
				i += ret;
			else
				return ;
		}
	}
	if (data->actual != 0)
		ft_putbuffer(data);
}

char		*ft_sprintf(const char *format, ...)
{
	t_printf	data;
	int			ret;
	va_list		ap;

	if (!format)
		return (NULL);
	ft_memset1(&data, 0, sizeof(t_printf));
	va_start(ap, format);
	detect_escape_char(format, &data, &ap);
	ret = data.ret;
	va_end(ap);
	return (data.result);
}
