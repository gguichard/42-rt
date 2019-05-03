/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:28:24 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:33:15 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_sprintf.h"

int		ft_strchr1(char needle, char *haystack)
{
	int		i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle)
			return (1);
		i++;
	}
	return (0);
}

int		free_error(void *ptr)
{
	free(ptr);
	return (ERROR);
}

void	ft_memset1(void *ptr, char c, int len)
{
	int				i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char*)ptr;
	while (i < len)
		tmp[i++] = c;
}

int		ft_strlen1(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_uppercase(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
}
