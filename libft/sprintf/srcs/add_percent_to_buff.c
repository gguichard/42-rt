/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_percent_to_buff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:06:32 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:03:07 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

void		add_percent_to_buffer(t_type *type, t_printf *data)
{
	unsigned int		width;

	width = (type->width < 0 ? -type->width : type->width);
	if (type->neg || type->width < 0)
	{
		ft_add_char_to_buff(data, '%');
		while (width-- > 1)
			ft_add_char_to_buff(data, ' ');
	}
	else
	{
		while (width-- > 1)
			ft_add_char_to_buff(data, ' ');
		ft_add_char_to_buff(data, '%');
	}
}
