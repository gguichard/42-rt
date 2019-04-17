/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:55:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/17 16:51:37 by gguichar         ###   ########.fr       */
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
	else if (error == ERR_INVALIDSCENE)
		return ("Scene file contains invalid characters");
	else if (error == ERR_SCENEBADFORMAT)
		return ("Scene file bad format");
	else if (error == ERR_SCENEBADOBJECT)
		return ("Scene bad object definition");
	else if (error == ERR_BADVEC3D)
		return ("Bad vec3d definition");
	else
		return ("Unknown error");
}
