/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:58:59 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 17:37:50 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_mouse_event(t_env *e)
{
	if (e->in.mousex > 5 && e->in.mousex < 5 + TILE_W && e->in.mousey > 5 && e->in.mousey < SCR_HEIGHT)
	{
		if (e->in.ywheel)
		{
			e->tex_index = ft_limit(e->tex_index + e->in.ywheel, 0, e->n_texture - N_TEX_DISP); 
			e->in.ywheel = 0;
		}
	}
	ft_env_display_mode(e);
}
