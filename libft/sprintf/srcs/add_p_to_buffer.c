/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_p_to_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:18:35 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:20:45 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include <stdlib.h>

static void	add_p2_to_buffer(t_type *type, t_printf *data, char *str, int i)
{
	int		len;

	len = ft_strlen1(str);
	type->width = (type->width < 0 ? -type->width : type->width);
	while (type->width-- > len)
		ft_add_char_to_buff(data, ' ');
	while (i >= 0)
		ft_add_char_to_buff(data, str[i--]);
	free(str);
}

static char	*convert_to_hexa(unsigned long long nbr, char *base)
{
	char				*str;
	unsigned int		i;

	if (!(str = (char*)malloc(sizeof(char) * 20)))
		return (NULL);
	i = 0;
	if (nbr == 0)
		str[i++] = '0';
	while (nbr > 0)
	{
		str[i] = base[nbr % 16];
		nbr /= 16;
		i++;
	}
	str[i++] = 'x';
	str[i++] = '0';
	str[i] = 0;
	return (str);
}

void		add_p_to_buffer(t_type *type, t_printf *data, va_list *ap)
{
	unsigned long long	addr;
	char				*str;
	int					i;

	addr = (unsigned long long)va_arg(*ap, void*);
	if (!(str = convert_to_hexa(addr, "0123456789abcdef")))
		return ;
	i = 0;
	while (str[i])
		i++;
	i--;
	if (type->neg || type->width < 0)
	{
		while (i >= 0)
			ft_add_char_to_buff(data, str[i--]);
	}
	add_p2_to_buffer(type, data, str, i);
}
