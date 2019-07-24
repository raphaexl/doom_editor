/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:38:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 09:16:53 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_env_load_textures(t_env *e)
{
	size_t	i;

	i = 0;
	e->n_texture = e->game.texture_count;
	e->textures = (t_sdl_texture *)malloc(sizeof(t_sdl_texture) * e->n_texture);
	while (i < e->n_texture)
	{
		if (!(e->textures[i].img = SDL_CreateTexture(e->sdl.renderer,
						SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
						e->game.textures[i].width, e->game.textures[i].height)))
			ft_sdl_error("Edition Texture Creation ");
		e->textures[i].w = 	e->game.textures[i].width; 
		e->textures[i].h = 	e->game.textures[i].height; 
		SDL_UpdateTexture(e->textures[i].img, NULL, e->game.textures[i].pixels,
				e->game.textures[i].width * sizeof(Uint32));
		i++;
	}
}
