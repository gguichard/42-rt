/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:50:19 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 23:11:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_error
{
	err_noerror = 0,
	err_unexpected,
	err_errno,
	err_sdlinit,
	err_noscenefile,
	err_invalidscene,
	err_scenebadformat,
	err_scenebadobject,
	err_badvec3d,
	err_badcolor,
	err_badobjfile
}				t_error;

const char		*error_to_str(t_error error);

#endif
