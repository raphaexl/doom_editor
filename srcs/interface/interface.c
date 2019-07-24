/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 17:58:01 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 10:34:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_interface_draw(t_env *e)
{
size_t			i;
	SDL_Rect		pos;
	SDL_Rect	d;

	i = 0;	
	d = (SDL_Rect){0, 0, TILE_W, TILE_H};
	i = e->tex_index < 0 ? 0 : e->tex_index > e->game.texture_count ?  e->game.texture_count - e->max_index : e->tex_index;
	while (i < e->max_index)
	{
		pos = (SDL_Rect){0, 0, e->textures[i].w, e->textures[i].h};
		d.x = 5;
		d.y = (i - e->tex_index) * TILE_H;
		SDL_RenderCopy(e->sdl.renderer, e->textures[i].img, &pos, &d);
		i++;
	}
}
