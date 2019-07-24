/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:09:15 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:34:28 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	ft_assign_intersect(t_intersect *inter, void *result,
double distance, int type)
{
	inter->object = result;
	inter->real_distance = distance;
	inter->type = type;
}

void		ft_intersect_portals(t_linked_list *portals, t_ray ray,
		t_intersect	*inter)
{
	t_portal	*portal;
	t_vector	res;
	double		distance;
	int			status;

	while (portals && (portal = portals->content))
	{
		status = 0;
		res = ft_intersect(ray, portal->wall, &status);
		if (status)
		{
			distance = ft_vector_distance(ray.pos, res);
			if (distance < inter->real_distance && distance > ray.dist)
			{
				ft_assign_intersect(inter, portal, distance, TYPE_PORTAL);
				inter->point = res;
			}
		}
		portals = portals->next;
	}
}

void		ft_intersect_walls(t_linked_list *walls, t_ray ray,
		t_intersect	*inter)
{
	t_wall		*wall;
	t_vector	res;
	double		distance;
	int			status;

	while (walls && (wall = walls->content))
	{
		status = 0;
		res = ft_intersect(ray, *wall, &status);
		if (status)
		{
			distance = ft_vector_distance(ray.pos, res);
			if (distance < inter->real_distance && distance > ray.dist)
			{
				ft_assign_intersect(inter, wall, distance, TYPE_WALL);
				inter->point = res;
			}
		}
		walls = walls->next;
	}
}

void		ft_intersect_objects(t_linked_list *objects, t_ray ray,
		t_intersect *inter, t_player *camera)
{
	t_object	*object;
	t_vector	res;
	t_wall		virtu_wall;
	double		distance;
	int			status;

	while (objects && (object = objects->content))
	{
		if (object != camera->object)
		{
			status = 0;
			if (object->properties & PROP_FIXED)
			{
				virtu_wall.p1.x = object->pos.x + object->radius * cos(object->angle + HALF_PI);
				virtu_wall.p1.y = object->pos.y + object->radius * sin(object->angle + HALF_PI);
				virtu_wall.p2.x = object->pos.x + object->radius * cos(object->angle - HALF_PI);
				virtu_wall.p2.y = object->pos.y + object->radius * sin(object->angle - HALF_PI);
			}
			else
			{
				virtu_wall.p1.x = object->pos.x + object->radius * cos(camera->object->angle + HALF_PI);
				virtu_wall.p1.y = object->pos.y + object->radius * sin(camera->object->angle + HALF_PI);
				virtu_wall.p2.x = object->pos.x + object->radius * cos(camera->object->angle - HALF_PI);
				virtu_wall.p2.y = object->pos.y + object->radius * sin(camera->object->angle - HALF_PI);
			}
			res = ft_intersect(ray, virtu_wall, &status);
			if (status)
			{
				distance = ft_vector_distance(ray.pos, res);
				if (distance < inter->real_distance && distance > ray.dist)
				{
					ft_assign_intersect(inter, object, distance, TYPE_OBJECT);
					inter->point = res;
				}
			}
		}
		objects = objects->next;
	}
}

void	ft_temp_draw_wall(t_graphic_render *env, t_intersect *inter, int x)
{
	t_point	top;
	t_point	bottom;
	int	height;

	top.x = x;
	bottom.x = x;
	height = (double)DEFAULT_WALLHEIGHT / inter->distance;
	top.y = env->camera->head_angle - height;
	bottom.y = env->camera->head_angle + height;
	ft_sdl_draw_line(env->image, top, bottom, 0xFF00FF);
}

void	ft_intersect_ray(t_graphic_render *env, t_raycast *raygen,
		t_sector *sec, int x)
{
	t_intersect	inter;
	t_ray		*ray;

	ray = &raygen->ray;
	ft_bzero(&inter, sizeof(t_intersect));
	inter.real_distance = MAX_RAY_DIST;
	ft_intersect_walls(sec->walls.first,
			*ray, &inter);
	ft_intersect_portals(sec->portals.first,
			*ray, &inter);
	ft_intersect_objects(sec->objects.first,
			*ray, &inter, env->camera);
	inter.sector = sec;
	inter.ray = ray;
	inter.distance = (double)inter.real_distance / ft_vector_size(&ray->dir);
	inter.render_min = raygen->render_min;
	inter.render_max = raygen->render_max;
	inter.screen_x = x;
	ray->dist = inter.real_distance;
	if (inter.type == TYPE_PORTAL)
	{
		inter.texture = &env->textures[((t_portal *)inter.object)->wall.texture];
		ft_draw_portal(env, &inter, x);
		raygen->render_min = inter.render_min;
		raygen->render_max = inter.render_max;
		ft_intersect_ray(env, raygen, ((t_portal *)inter.object)->sector, x);
	}
	else if (inter.type == TYPE_WALL)
	{
		if (GET_WALL((&inter))->properties & PROP_TRANSPARENT)
			ft_intersect_ray(env, raygen, sec, x);
		inter.texture = &env->textures[((t_wall *)inter.object)->texture];
		ft_draw_wall(env, &inter, x);
	}
	else if (inter.type == TYPE_OBJECT)
	{
		ft_intersect_ray(env, raygen, sec, x);
		inter.texture = &env->textures[((t_wall *)inter.object)->texture];
		ft_draw_object(env, &inter, x);
	}
}
