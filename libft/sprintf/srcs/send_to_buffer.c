/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:27:59 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:03:43 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

void	send_to_buffer(t_type *type, t_printf *data, va_list *ap)
{
	if (type->conv == 'c')
		add_c_to_buffer(type, data, ap);
	else if (type->conv == 's')
		add_s_to_buffer(type, data, ap);
	else if (type->conv == 'p')
		add_p_to_buffer(type, data, ap);
	else if (type->conv == 'd' || type->conv == 'i')
		add_d_to_buffer(type, data, ap);
	else if (type->conv == 'o')
		add_o_to_buffer(type, data, ap);
	else if (type->conv == 'u')
		add_u_to_buffer(type, data, ap);
	else if (type->conv == 'x')
		add_x_to_buffer(type, data, ap);
	else if (type->conv == 'X')
		add_xmaj_to_buffer(type, data, ap);
	else if ((type->conv == 'f' || type->conv == 'F')
		&& (type->l || !type->warning))
		add_f_to_buffer(type, data, ap);
	else if (type->conv == '%')
		add_percent_to_buffer(type, data);
}
