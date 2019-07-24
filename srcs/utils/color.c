/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:04:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 14:11:42 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/editor.h"

SDL_Color	ft_sdl_color(Uint32 c)
{
	SDL_Color color;

	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		color.r = (c >> 16) & 0xFF;
		color.g = (c >> 8) & 0xFF;
		color.b = (c) & 0xFF;
		color.a = (c >> 24) & 0xFF;
	}
	else
	{
		color.r = (c >> 24) & 0xFF;
		color.g = (c >> 16) & 0xFF;
		color.b = (c >> 8) & 0xFF;
		color.a = (c & AMASK);
	}
	return (color);
}

Uint32	ft_color_sdl(SDL_Color c)
{
	return ((c.r << 24) + (c.g << 16) + (c.b << 8) + c.a);
}
