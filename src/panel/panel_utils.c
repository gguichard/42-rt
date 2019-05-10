/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:04:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/10 18:58:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"

static void	buf_llong(long long value, char *buffer)
{
	buffer--;
	if (value >= 10)
		buf_llong(value / 10, buffer);
	else if (value <= -10)
		buf_llong(-(value / 10), buffer);
	*buffer = ft_abs(value % 10) + '0';
}

char		*double_as_string(double value, unsigned int precision)
{
	double			inte;
	long long int	inte_as_llong;
	long long int	frac_as_llong;
	int				len;
	char			*buffer;

	frac_as_llong = (long long int)(modf(value, &inte) * pow(10, precision));
	inte_as_llong = (long long int)inte;
	len = ft_llsize(inte_as_llong) + precision + 1;
	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer != NULL)
	{
		buffer[len] = '\0';
		ft_memset(buffer, '0', len - 1);
		if (inte_as_llong < 0)
			buffer[0] = '-';
		buffer[ft_llsize(inte_as_llong)] = '.';
		buf_llong(inte_as_llong, buffer + ft_llsize(inte_as_llong));
		buf_llong(frac_as_llong, buffer + len);
	}
	return (buffer);
}
