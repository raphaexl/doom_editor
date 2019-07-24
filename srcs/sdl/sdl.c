/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:02:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 16:11:42 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int		ft_sdl_window(t_sdl *s, const char *title)
{
	SDL_Surface *ico;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		ft_sdl_error("Initialisation : ");
	TTF_Init();
	if (!(s->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN)))
		ft_sdl_error("Window creation failed : ");
	if (!(s->renderer = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_sdl_error("Renderer creation failed : ");
	if (!(s->g_texture = SDL_CreateTexture(s->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, GAME_W, GAME_H)))
		ft_sdl_error("Game Texture Creation ");
	if (!(s->e_texture = SDL_CreateTexture(s->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, EDIT_W, EDIT_H)))
		ft_sdl_error("Edition Texture Creation ");
	s->g_pos = (SDL_Rect){G_START_X, G_START_Y, GAME_W, GAME_H};
	s->e_pos = (SDL_Rect){E_START_X, E_START_Y, EDIT_W, EDIT_H};
	if ((ico = IMG_Load("data/imgs/SDL_Logo.png")))
	{
		SDL_SetWindowIcon(s->window, ico);
		SDL_FreeSurface(ico);
	}
	ico = NULL;
	return (0);
}


int			ft_sdl_update(t_sdl *s, t_img *g_img, t_img *e_img, int state)
{
	SDL_Rect	d;

	d = (SDL_Rect){.x = G_START_X, .y = G_START_Y,
		.w = GAME_W, .h = GAME_H};
	if (state)
	{
	SDL_UpdateTexture(s->g_texture, NULL, g_img->pixels, GAME_W * sizeof(Uint32));
	SDL_RenderCopy(s->renderer, s->g_texture, NULL, &d);
	}
	else
	{
	d = (SDL_Rect){.x = E_START_X, .y = E_START_Y,
		.w = EDIT_W, .h = EDIT_H};
	SDL_UpdateTexture(s->e_texture, NULL, e_img->pixels, EDIT_W * sizeof(Uint32));
	SDL_RenderCopy(s->renderer, s->e_texture, NULL, &d);
	}
	return (0);
}

void		ft_sdl_quit(t_sdl *s)
{
	if (s->g_texture)
		SDL_DestroyTexture(s->g_texture);
	s->g_texture = NULL;
	if (s->e_texture)
		SDL_DestroyTexture(s->e_texture);
	s->e_texture = NULL;
	if (s->renderer)
		SDL_DestroyRenderer(s->renderer);
	s->renderer = NULL;
	if (s->window)
		SDL_DestroyWindow(s->window);
	s->window = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
