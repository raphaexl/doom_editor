/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:10:44 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/22 16:11:17 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

/*
**	This function draw a vertical texture line from p1.y to p2.y
**		it first calculates the texture increment unit for mapping
**		then calculates only the interval that will be drawn
**		from draw_y.FIRST to draw_y.SECOND then calculates the line position
**		from the start of the wall in p2->x
**		maps the draw_y.FIRST to the texture height in y
**		then procedes drawing, and increments by the CONFIG_RES_RATIO
*/

void	ft_draw_texture_line(t_graphic_render *env, t_point *p1, t_point *p2,
		t_intersect *inter)
{
	t_texture	*tex;
	t_pair		draw_y;
	double		unit;
	double		y;
	char		transparent;

	tex = inter->texture;
	if (inter->type == TYPE_WALL && GET_WALL(inter)->properties & PROP_TRANSPARENT)
		transparent = 1;
	unit = tex->height / ((double)DEFAULT_WALLHEIGHT / inter->distance);
	draw_y.FIRST = ft_limit(p1->y, inter->render_min, inter->render_max);
	draw_y.SECOND = ft_limit(p2->y, inter->render_min, inter->render_max);
	p2->x = ft_vector_distance(
			(inter->type == TYPE_PORTAL) ? GET_PORT(inter)->wall.p1 :
			GET_WALL(inter)->p1, inter->point);
	y = (draw_y.FIRST - p1->y) * unit;
	while (draw_y.FIRST < draw_y.SECOND)
	{
		if (!transparent || RGB_A(TEX_PIX(tex, p2->x, y)))
			ft_place_pixel(env->image, p1->x, draw_y.FIRST,
					ft_brightness(TEX_PIX(tex, p2->x, y), inter->sector->brightness));
		draw_y.FIRST += CONFIG_RES_RATIO;
		y += unit * CONFIG_RES_RATIO;
	}
}

/*
**	This function calculates the x and y position of each pixel in the ceiling
**		and maps it and adds textures
*/

void	ft_draw_ceiling(t_graphic_render *env, t_pair draw_y,
		t_intersect *inter, double wall_height)
{
	t_texture		*tex;
	t_vector		link;
	t_float_pair	dist_size;
	double			temp_y;

	if (inter->sector->ceil_tex < 0)
		return ;
	tex = &env->textures[inter->sector->ceil_tex];
	temp_y = wall_height;
	wall_height *= inter->distance;
	link.x = inter->point.x - env->camera->pos->x;
	link.y = inter->point.y - env->camera->pos->y;
	dist_size.SECOND = ft_vector_size(&link);
	while (draw_y.FIRST >= draw_y.SECOND)
	{
		if (ft_is_inrange(draw_y.FIRST, inter->render_min, inter->render_max))
		{
			if ((dist_size.FIRST = (((double)(wall_height) / (double)(temp_y)) *
				ft_vector_size(&(inter->ray->dir))) / dist_size.SECOND) < 0)
				break ;
			ft_place_pixel(env->image, inter->screen_x, draw_y.FIRST,
				ft_brightness(TEX_PIX(tex, (env->camera->pos->x + link.x * dist_size.FIRST),
				(env->camera->pos->y + link.y * dist_size.FIRST)), inter->sector->brightness));
		}
		temp_y -= CONFIG_RES_RATIO;
		draw_y.FIRST -= CONFIG_RES_RATIO;
	}
}

/*
**	This function calculates the x an y position of each pixel in the ceiling
**		and maps it and adds texture
*/

void	ft_draw_floor(t_graphic_render *env, t_pair draw_y,
		t_intersect *inter, double wall_height)
{
	t_texture		*tex;
	t_vector		link;
	t_float_pair	dist_size;
	double			temp_y;

	if (inter->sector->floor_tex < 0)
		return ;
	tex = &env->textures[inter->sector->floor_tex];
	temp_y = wall_height;
	wall_height *= inter->distance;
	link.x = inter->point.x - env->camera->pos->x;
	link.y = inter->point.y - env->camera->pos->y;
	dist_size.SECOND = ft_vector_size(&link);
	while (draw_y.FIRST <= draw_y.SECOND)
	{
		if (ft_is_inrange(draw_y.FIRST, inter->render_min, inter->render_max))
		{
			if ((dist_size.FIRST = (((double)(wall_height) / (double)(temp_y)) *
				ft_vector_size(&(inter->ray->dir))) / dist_size.SECOND) < 0)
				break ;
			ft_place_pixel(env->image, inter->screen_x, draw_y.FIRST,
				ft_brightness(TEX_PIX(tex ,(env->camera->pos->x + link.x * dist_size.FIRST)
					,(env->camera->pos->y + link.y * dist_size.FIRST)), inter->sector->brightness));
		}
		temp_y += CONFIG_RES_RATIO;
		draw_y.FIRST += CONFIG_RES_RATIO;
	}
}

