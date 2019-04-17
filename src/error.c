/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:55:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 10:57:30 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "SDL.h"
#include "error.h"

const char	*error_to_str(t_error error)
{
	if (error == ERR_UNEXPECTED)
		return ("Unexpected error");
	else if (error == ERR_ERRNO)
		return (strerror(errno));
	else if (error == ERR_SDLINIT)
		return (SDL_GetError());
	else
		return ("Unknown error");
}
