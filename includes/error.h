/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:50:19 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/24 03:37:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_error
{
	ERR_NOERROR = 0,
	ERR_UNEXPECTED,
	ERR_ERRNO,
	ERR_SDLINIT,
	ERR_INVALIDSCENE,
	ERR_SCENEBADFORMAT,
	ERR_SCENEBADOBJECT,
	ERR_BADVEC3D,
	ERR_BADCOLOR,
	ERR_BADOBJFILE
}				t_error;

const char		*error_to_str(t_error error);

#endif
