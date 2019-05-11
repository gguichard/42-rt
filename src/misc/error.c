/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:55:24 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:11:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "SDL.h"
#include "error.h"

const char	*error_to_str(t_error error)
{
	if (error == err_unexpected)
		return ("Unexpected error");
	else if (error == err_errno)
		return (strerror(errno));
	else if (error == err_sdlinit)
		return (SDL_GetError());
	else if (error == err_noscenefile)
		return ("Please specify a scene file");
	else if (error == err_invalidscene)
		return ("Scene file contains invalid characters");
	else if (error == err_scenebadformat)
		return ("Scene file bad format");
	else if (error == err_scenebadobject)
		return ("Scene bad object definition");
	else if (error == err_badvec3d)
		return ("Bad vec3d definition");
	else if (error == err_badcolor)
		return ("Bad color definition");
	else if (error == err_badobjfile)
		return ("Bad .obj file\n");
	else
		return ("Unknown error");
}
