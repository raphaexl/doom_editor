/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:52:21 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 14:44:34 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include "input.h"
# include "prototypes.h"
# include <stdio.h>

typedef struct	s_env
{
	t_game			game;
	t_sdl			sdl;
	t_input			in;
	t_button		*buttons;
	t_img			*g_img;
	t_img			*e_img;
	t_point			offset;
	int				tex_index;
	int				max_index;
	int				n_texture;
	int				renderer_state;
	t_sdl_texture	*textures;
}				t_env;

t_point		ft_point(int x, int y);
void		ft_sdl_clear_pixels(t_img *img, int color);
void		ft_sdl_put_pixel(t_img *pixels, int x, int y, int color);
void		ft_sdl_draw_octant1(t_img *ps, t_point p, t_point q, Uint32 c);
void		ft_sdl_draw_octant2(t_img *ps, t_point p, t_point q, Uint32 c);
void		ft_sdl_draw_line(t_img *ps, t_point p, t_point q, Uint32 c);
void		ft_sdl_draw_disc(t_img *ps, t_point co, int radius, Uint32 col);
void		ft_sdl_draw_rect(t_img *ps, t_rect rect, Uint32 c);

int			ft_sdl_window(t_sdl *sdl, const char *title);
int			ft_sdl_update(t_sdl *s, t_img *g_img, t_img * e_img, int state);
void		ft_update_event(t_input *in);
void		ft_sdl_quit(t_sdl *s);

int			ft_env_init(t_env *e);
int			ft_env_draw(t_env *e);
void		ft_env_event(t_env *e);
int			ft_env_quit(t_env *e);
t_img		*ft_img_create(int w, int h, Uint32 color);
void		ft_sdl_error(char *error);


void		ft_sector_print(t_sector *sect, Uint32 count);
void		ft_edit_draw(t_env *e);
void		ft_interface_draw(t_env *e);
void		ft_env_load_textures(t_env *e);

void		ft_env_buttons_init(t_env *e);
void		ft_env_display_mode(t_env *e);
void		ft_buttons_draw(t_env *e);

void		ft_mouse_event(t_env *e);
int			ft_mouse_on(struct s_button *, int x, int y);
int			ft_mouse_on_button(t_button *b, int x, int y);
int			ft_mouse_on_sector(t_button *b, int x, int y);
void		ft_sector_draw(t_env *e);

SDL_Color	ft_sdl_color(Uint32 c);
Uint32		ft_color_sdl(SDL_Color c);
void		ft_add_player(t_game	*game);
t_font		ft_font(const char *message, const char *font_file, int font_size);
SDL_Texture	*ft_get_render_text(SDL_Renderer *rend, t_font f, SDL_Color color);
#endif

