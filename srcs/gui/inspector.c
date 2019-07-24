/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:30:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 21:54:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_inspector_init(t_env *e)
{
	e->inspector.sector_no = 0;
	e->inspector.link_sectors = ft_get_sectors_list(e);
	e->inspector.content = NULL;
	ft_button_push_back(&e->inspector.content, ft_button_new(ie->sdl.renderer, "SECTOR 0", 0xFFFF00FF));	
}


void	ft_inspector_draw(t_env *e)
{
		
}
