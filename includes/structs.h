/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 16:03:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 14:43:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "defs.h"

typedef	struct		s_rect
{
	int		x;
	int		y;
	int		w;
	int		h;
}					t_rect;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_vec2
{
	float	x;
	float	y;
}				t_vec2;

typedef struct s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*g_texture;
	SDL_Texture		*e_texture;
	SDL_Rect		g_pos;
	SDL_Rect		e_pos;
}				t_sdl;

typedef struct	s_img
{
	Uint32		*pixels;
	int			w;
	int			h;
}				t_img;

typedef struct	s_sdl_texture
{
	SDL_Texture	*img;
	int			w;
	int			h;
}				t_sdl_texture;

typedef	struct	s_font
{
	char		*mes;
	char		*file;
	int			size;
}				t_font;

typedef	struct	s_button
{
	int			id;
	SDL_Rect	pos;
	char		*text;
	SDL_Texture	*img;
	Uint32		color;
	int			(*ft_mouse_on)(struct s_button *, int x, int y);
	struct	s_button	*next;
}				t_button;

typedef struct	s_scroll_bar
{
	int						id;
	t_img					*img;
	SDL_Rect				pos;
	double					min;
	double					max;
	SDL_Rect				curs_pos;
	struct s_scroll_bar		*next;
}				t_scroll_bar;


typedef struct		s_entry
{
	SDL_Rect		pos[2];
	char			*mes;
	Uint32			color;
	int				id;
	struct s_entry	*next;
}					t_entry;
#endif
