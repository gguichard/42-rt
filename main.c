/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 13:44:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/11 14:05:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"

#include <stdio.h>

__attribute__((destructor))
void lol()
{
	while (1) ;
}

int	main(void)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Quit();
}
