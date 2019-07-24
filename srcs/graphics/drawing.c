/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:04:58 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/22 16:44:30 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

Uint32	ft_brightness(Uint32 color, double brightness)
{
	return ((((int)((double)RGB_R(color) * brightness) << 16) |
			((int)((double)RGB_G(color) * brightness) << 8) |
			(int)((double)RGB_B(color) * brightness)));
}

/*
**	This function places a pixel on the screen, but takes into consideration
**		the CONFIG_RES_RATIO
*/

void	ft_place_pixel(t_img *img, int x, int y, Uint32 color)
{
	int	temp_x;
	int	temp_y;

	temp_y = 0;
	x -= x % CONFIG_RES_RATIO;
	y -= y % CONFIG_RES_RATIO;
	while (temp_y < CONFIG_RES_RATIO)
	{
		temp_x = 0;
		while (temp_x < CONFIG_RES_RATIO)
		{
			ft_sdl_put_pixel(img, x + temp_x, y + temp_y, color);
			temp_x++;
		}
		temp_y++;
	}
}

/*
**	This function calculates all the necessary values to draw a wall
**		- first calculates the final height of the wall
**		- calculates the top and bottom points y in the screen
**		- calls a function to draw the texture from top to bottom
**		- calls a function to draw the floor from bottom to render_max
**		- calls a function to draw the ceiling from top to render_min
*/

void	ft_draw_wall(t_graphic_render *env, t_intersect *inter, int x)
{
	t_wall	*wall;
	t_point	top;
	t_point	bottom;
	double	height;

	top.x = x;
	bottom.x = x;
	wall = inter->object;
	height = (double)(DEFAULT_WALLHEIGHT + inter->sector->floor_height +
			inter->sector->ceil_height) / inter->distance;
	bottom.y = env->camera->head_angle + ((env->camera->cam_height +
				inter->sector->floor_height) / inter->distance);
	top.y = bottom.y - height;
	ft_draw_texture_line(env, &top, &bottom, inter);
	ft_draw_floor(env, (t_pair){bottom.y, inter->render_max}, inter,
			(double)(env->camera->cam_height + inter->sector->floor_height)
			/ inter->distance);
	ft_draw_ceiling(env, (t_pair){top.y, inter->render_min}, inter,
			(double)(env->camera->cam_height + inter->sector->floor_height)
			/ inter->distance - height);
}

/*
**	This function draws the top part of a portal
**		- first it calculates the portal height
**		- calculates the top and bottom y values of that top part
**		- calls a function to draw the ceiling from top to render_min
*/

void	ft_draw_portal_top(t_graphic_render *env, t_intersect *inter, int x)
{
	t_portal	*portal;
	t_point		top;
	t_point		bottom;
	double		height;

	portal = inter->object;
	top.x = x;
	bottom.x = x;
	height = (double)(DEFAULT_WALLHEIGHT + inter->sector->ceil_height -
			env->camera->cam_height) / inter->distance;
	top.y = env->camera->head_angle - height;
	bottom.y = top.y + (inter->sector->ceil_height -
			portal->sector->ceil_height) / inter->distance;
	bottom.y = ft_min(bottom.y, env->camera->head_angle + (env->camera->cam_height + inter->sector->floor_height) / inter->distance);
	if (top.y < bottom.y)
		ft_draw_texture_line(env, &top, &bottom, inter);
	ft_draw_ceiling(env, (t_pair){top.y, inter->render_min}, inter,
			(double)(env->camera->cam_height - DEFAULT_WALLHEIGHT -
				inter->sector->ceil_height) / inter->distance);
	top.y = ft_limit(top.y, inter->render_min, inter->render_max);
	bottom.y = ft_limit(bottom.y, inter->render_min, inter->render_max);
	inter->render_min = ft_max(top.y, bottom.y);
}

/*
**	This function draws the bottom part of a portal
**		- first it calculates the portal height
**		- calculates the top and bottom y values of that bottom part
**		- calls a function to draw the ceiling from bottom to render_max
*/

void	ft_draw_portal_bottom(t_graphic_render *env, t_intersect *inter, int x)
{
	t_portal	*portal;
	t_point		top;
	t_point		bottom;
	int			height;

	portal = inter->object;
	top.x = x;
	bottom.x = x;
	height = (env->camera->cam_height + inter->sector->floor_height)
		/ inter->distance;
	bottom.y = env->camera->head_angle + height;
	top.y = bottom.y - (inter->sector->floor_height -
			GET_PORT(inter)->sector->floor_height) / inter->distance;
	if (top.y < bottom.y)
		ft_draw_texture_line(env, &top, &bottom, inter);
	ft_draw_floor(env, (t_pair){bottom.y, inter->render_max}, inter,
			(double)(env->camera->cam_height + inter->sector->floor_height)
			/ inter->distance);
	top.y = ft_limit(top.y, inter->render_min, inter->render_max);
	bottom.y = ft_limit(bottom.y, inter->render_min, inter->render_max);
	inter->render_max = ft_min(top.y, bottom.y);
}

/*
**	this function just calls the ft_draw_portal_top and ft_draw_portal_bottom
**		functions
*/

void	ft_draw_portal(t_graphic_render *env, t_intersect *inter, int x)
{
	ft_draw_portal_top(env, inter, x);
	ft_draw_portal_bottom(env, inter, x);
}

/*
**	this function maps a texture to the object
*/

void	ft_object_texture(t_intersect *inter, double x_ratio, int y1, int y2, t_texture *texture, t_graphic_render *map)
{
	int	tex_y;
	int	y;
	int tex_x;
	double	y_ratio;
	Uint32	color;

	y_ratio = (double)texture->height / (double)(y2 - y1);
	y = ft_limit(y1, inter->render_min, inter->render_max);
	tex_x = x_ratio * texture->width;
	y2 = ft_min(y2, map->camera->head_angle + (map->camera->cam_height + inter->sector->floor_height) / inter->distance);
	while (y <= y2 && y < inter->render_max)
	{
		tex_y = y_ratio * (y - y1);
		color = texture->pixels[((tex_y % texture->height) * texture->width) + (tex_x % texture->width)];
		if (RGB_A(color))
			ft_place_pixel(map->image, inter->screen_x, y, ft_brightness(color, inter->sector->brightness));
		y++;
	}
}
/*
**	this funtion will draw an object
*/

void	ft_draw_object(t_graphic_render *env, t_intersect *inter, int x)
{
	t_object	*object;
	t_point		pp;
	int			top;
	int			bottom;
	double		size;
	double		anglediff;
	double		posratio;
	int			texture_index;

	(void)x;
	object = inter->object;
	size = object->size / inter->distance;
	top = env->camera->head_angle - object->height / inter->distance + env->camera->cam_height / inter->distance - size;
	bottom = top + 2 * size;
	if (object->properties & PROP_FIXED)
		pp = (t_point){object->pos.x + object->radius * cos(object->angle + HALF_PI),
			object->pos.y + object->radius * sin(object->angle + HALF_PI)};
	else
		pp = (t_point){object->pos.x + object->radius * cos(env->camera->object->angle + HALF_PI),
			object->pos.y + object->radius * sin(env->camera->object->angle + HALF_PI)};

	posratio = ft_vector_distance(pp, inter->point);
	anglediff = object->angle - env->camera->object->angle;
	if (anglediff < 0)
		anglediff = M_PI - anglediff;
	texture_index = ((int)((anglediff) / (double)(2*M_PI/(double)object->tex_count) + 2 * M_PI / object->tex_count) % object->tex_count);
	ft_object_texture(inter, ((double)posratio / ((double)object->radius * 2)), top, bottom, &inter->texture[texture_index], env);
}
