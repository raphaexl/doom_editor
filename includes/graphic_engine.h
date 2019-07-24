/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_engine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:02:05 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 14:43:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_ENGINE_H
# define GRAPHIC_ENGINE_H
# include "utils.h"
# define FIRST x
# define SECOND y
# define TEX_PIX(t, x, y) (t->pixels[ft_modulus(y, t->height) * t->width\
	   	+ ft_modulus(x, t->width)])

typedef	struct	s_point		t_pair;
typedef	struct	s_vector	t_float_pair;
typedef	struct	s_img		t_img;

/*
**	interface functions
*/

int			ft_render_graphics(t_graphic_render	*env);

/*
**	intersection functions
*/

t_vector	ft_intersect(t_ray ray, t_wall wall, int *status);
t_vector	ft_segment_intersect(t_point player, t_vector dir, t_wall wall,
	int *status);
double	ft_segment_distance_sq(t_point player_pos, t_point p1, t_point p2);

/*
**	drawing functions
*/

void		ft_place_pixel(t_img *img, int x, int y, Uint32 color);
void		ft_draw_wall(t_graphic_render *env, t_intersect *inter, int x);
void		ft_draw_portal(t_graphic_render *env, t_intersect *inter, int x);
void		ft_draw_object(t_graphic_render *env, t_intersect *inter, int x);

/*
**	texturing functions
*/

void		ft_draw_texture_line(t_graphic_render *env, t_point *p1,
		t_point *p2, t_intersect *inter);
void		ft_draw_ceiling(t_graphic_render *env, t_pair draw_y,
		t_intersect *inter, double wall_height);
void		ft_draw_floor(t_graphic_render *env, t_pair draw_y,
		t_intersect *inter, double wall_height);

/*
** brightness and effects
*/

Uint32	ft_brightness(Uint32 color, double brightness);
#endif
