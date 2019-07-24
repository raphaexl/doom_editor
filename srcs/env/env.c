/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:02:19 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 10:09:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int		ft_env_init(t_env *e)
{
	ft_bzero(&e->game, sizeof(t_game));
	if (!(e->game.sectors = ft_load_sectors("map00", &e->game)))
	{
		ft_putendl("Could not load sectors");
		return (-1);
	}
	ft_sector_print(e->game.sectors, e->game.sector_count);
	if (!(e->game.renderer.image = ft_img_create(GAME_W, GAME_H, 0xFF00FFFF)))
	ft_putendl("GRAPHIC_RENDERER");
	if (!(e->g_img = ft_img_create(GAME_W, GAME_H, 0xFF00FFFF)))
	ft_putendl("GAME_W");
	if (!(e->e_img = ft_img_create(EDIT_W, EDIT_H, 0xFFFF00FF)))
	ft_putendl("EDIT_W");
	ft_add_player(&e->game);
	ft_sdl_window(&e->sdl, "1337");
	ft_env_load_textures(e);
	e->max_index = e->tex_index + N_TEX_DISP <= e->game.texture_count ? e->tex_index + N_TEX_DISP : e->game.texture_count;
	ft_env_buttons_init(e);
	e->renderer_state = 0;
	return (0);
}

void	ft_env_event(t_env *e)
{
	ft_update_event(&e->in);
	ft_mouse_event(e);
	e->game.in = e->in;
	ft_keyboard_handling(&e->game);
	e->game.delta_time = (double)(SDL_GetTicks() - e->game.last_time) / 1000.0;
	e->game.last_time = SDL_GetTicks();
}

int		ft_env_draw(t_env *e)
{
	SDL_RenderClear(e->sdl.renderer);
	ft_edit_draw(e);
	ft_render_graphics(&e->game.renderer);
	ft_sdl_update(&e->sdl, e->game.renderer.image, e->e_img, e->renderer_state);
	//ft_sdl_update(&e->sdl, e->g_img, e->e_img);
	ft_interface_draw(e);
	ft_buttons_draw(e);
	SDL_RenderPresent(e->sdl.renderer);
	return (0);
}

int		ft_env_quit(t_env *e)
{
	ft_button_clean(&e->buttons);
	ft_sdl_quit(&e->sdl);
	return (0);
}
