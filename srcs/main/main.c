/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:22:30 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 16:36:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int		main(void)
{
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	ft_env_init(&e);
	while (!e.in.quit)
	{
		ft_env_event(&e);
		ft_env_draw(&e);
	//	SDL_Delay(1);
	}
	ft_env_quit(&e);
	return (0);
}
