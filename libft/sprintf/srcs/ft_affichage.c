/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affichage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:27:19 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:28:18 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_sprintf.h"

void		ft_add_char_to_buff(t_printf *data, char c)
{
	data->buffer[data->actual++] = c;
	if (data->actual == BUFF_SIZE)
		ft_putbuffer(data);
}

static char	*join_string_to_result(t_printf *data)
{
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (data->result)
	{
		if (!(tmp = (char*)malloc(sizeof(char)
						* (data->actual + ft_strlen1(data->result) + 1))))
			return (NULL);
		while (data->result[i])
		{
			tmp[i] = data->result[i];
			i++;
		}
	}
	else if (!(tmp = (char*)malloc(sizeof(char) * (data->actual + 1))))
		return (NULL);
	j = 0;
	while (j < data->actual)
		tmp[i++] = data->buffer[j++];
	tmp[i] = 0;
	free(data->result);
	return (tmp);
}

void		ft_putbuffer(t_printf *data)
{
	if (!(data->result = join_string_to_result(data)))
		return ;
	data->ret += data->actual;
	data->actual = 0;
}
