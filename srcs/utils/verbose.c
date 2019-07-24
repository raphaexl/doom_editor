/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:46:57 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:40:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/editor.h"

t_font		ft_font(const char *message, const char *font_file, int font_size)
{
	t_font	f;

	f.mes = (char *)message;
	f.file = (char *)font_file;
	f.size = font_size;
	return (f);
}

SDL_Texture	*ft_get_render_text(SDL_Renderer *rend, t_font f, SDL_Color color)
{
	TTF_Font		*font;
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	font = NULL;
	surface = NULL;
	texture = NULL;
	font = TTF_OpenFont(f.file, f.size);
	if (!font)
		ft_putendl(TTF_GetError());
	if (!(surface = TTF_RenderText_Blended(font, f.mes, color)))
		ft_printf("Error creating surface ttf");
	if (!(texture = SDL_CreateTextureFromSurface(rend, surface)))
		ft_printf("Error making texture ttf");
	SDL_FreeSurface(surface);
	if (!font)
		perror(TTF_GetError());
	TTF_CloseFont(font);
	return (texture);
}
