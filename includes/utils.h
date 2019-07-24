/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:15:59 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 14:43:16 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "input.h"
# include "graphic_engine.h"

typedef struct	s_game		t_game;
typedef struct	s_sector	t_sector;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef	struct	s_texture
{
	Uint32		*pixels;
	Uint32		width;
	Uint32		height;
}				t_texture;

typedef struct	s_wall
{
	t_point		p1;
	t_point		p2;
	Uint32		texture;
	Uint32		properties;
}				t_wall;

typedef struct	s_portal
{
	t_sector	*sector;
	t_wall		wall;
}				t_portal;


typedef	struct	s_object
{
	t_point			pos;
	Uint32			radius;
	Uint32			size;
	Uint32			texture;
	Uint32			tex_count;
	Uint32			height;
	double			angle;
	t_linked_list	*parent;
	Uint32			properties;
}				t_object;

typedef struct	s_sector
{
	t_linked_list_head	walls;
	t_linked_list_head	portals;
	t_linked_list_head	objects;
	int					floor_height;
	int					ceil_height;
	int					floor_tex;
	int					ceil_tex;
	double				brightness;
}				t_sector;

typedef	struct	s_player
{
	t_sector	*sector;
	t_object	*object;
	t_point		*pos;
	t_vector	speed;
	t_vector	velocity;
	double		zspeed;
	int			cam_height;
	int			head_angle;
	int			height;
	int			crouch_height;
}				t_player;

typedef	struct	s_graphic_render
{
	t_img		*image;
	t_texture	*textures;
	t_player	*camera;
	int			sky_texture;
	int			texture_count;
}				t_graphic_render;

typedef struct	s_game
{
	t_graphic_render	renderer;
	t_input				in;
	t_player			*main_player;
	t_player			*players;
	t_texture			*textures;
	t_sector			*sectors;
	Uint32				sector_count;
	Uint32				texture_count;
	Uint32				last_time;
	Uint32				sky_texture;
	double				delta_time;
	Uint32				options;
}				t_game;


typedef struct	s_segment_distance
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	dot;
	double	len_sq;
	double	param;
	double	xx;
	double	yy;
	double	dx;
	double	dy;
}				t_segment_distance;

typedef	struct	s_ray
{
	t_point		pos;
	t_vector	dir;
	double		dist;
}				t_ray;

typedef	struct	s_intersect
{
	void		*object;
	t_sector	*sector;
	t_texture	*texture;
	t_ray		*ray;
	double		distance;
	double		real_distance;
	int			render_min;
	int			render_max;
	double		texture_map_ratio;
	int			screen_x;
	Uint32		type;
	t_vector	point;
}				t_intersect;


typedef	struct	s_raycast
{
	t_vector	direction;
	t_vector	plane;
	t_vector	swipe;
	t_ray		ray;
	int			render_min;
	int			render_max;
	int			iter;
}				t_raycast;

typedef	struct			s_intercalc
{
	t_vector			p1;
	t_vector			p2;
	t_vector			p3;
	t_vector			p4;
	double				den;
	double				u;
	double				t;
}						t_intercalc;

typedef struct	s_inspector
{
	int			sector_no;
	t_sector	*sector;
	t_button	*content;
}				t_inspector;
#endif
