/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:11:23 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 16:11:46 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSG_H
# define CSG_H

# define CSGACTION_MISS (1 << 0)
# define CSGACTION_RETLIFCLOSER (1 << 1)
# define CSGACTION_RETLIFFARTHER (1 << 2)
# define CSGACTION_RETL (1 << 3)
# define CSGACTION_RETRIFCLOSER (1 << 4)
# define CSGACTION_RETRIFFARTHER (1 << 5)
# define CSGACTION_RETR (1 << 6)
# define CSGACTION_FLIPR (1 << 7)
# define CSGACTION_LOOPL (1 << 8)
# define CSGACTION_LOOPR (1 << 9)
# define CSGACTION_LOOPLIFCLOSER (1 << 10)
# define CSGACTION_LOOPRIFCLOSER (1 << 10)

# define CSGHIT_ENTER 0
# define CSGHIT_EXIT 1
# define CSGHIT_MISS 2

#endif
