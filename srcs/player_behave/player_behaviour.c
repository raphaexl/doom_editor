/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_behaviour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 22:21:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 09:10:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int		ft_should_stop(t_point old, t_point new, t_wall *wall, double distance)
{
	double olddist;
	double newdist;

	olddist = ft_segment_distance_sq(old, wall->p1, wall->p2);
	newdist = ft_segment_distance_sq(new, wall->p1, wall->p2);
	if (newdist < distance && newdist < olddist)
		return (1);
	return (0);
}

/*
 * **	This function checks all portals in the current sector and checks if the
 * **		player is traversing that portal, then changes the current sector
 * **		to the new one
 * */

int			ft_portal_traversal(t_player *p, double distance)
{
	t_linked_list	*portals;
	t_portal		*portal;
	t_point			newpos;
	int				status;
	int				stop;

	portals = p->sector->portals.first;
	newpos = (t_point){p->pos->x + p->speed.x, p->pos->y + p->speed.y};
	while (portals)
	{
		portal = portals->content;
		ft_segment_intersect(*p->pos, p->speed, portal->wall, &status);
		stop = ft_should_stop(*p->pos, newpos, &portal->wall, distance);
		if (stop && (p->cam_height - p->height < -portal->sector->floor_height
		|| p->cam_height > portal->sector->ceil_height + DEFAULT_WALLHEIGHT))
		{
			p->speed.x = 0;
			p->speed.y = 0;
			p->zspeed = 0;
			return (1);
		}
		if (status)
		{
			ft_list_delete(&p->sector->objects, p->object->parent);
			p->sector = portal->sector;
			ft_list_push(&p->sector->objects, p->object->parent);
		}
		portals = portals->next;
	}
	return (0);
}

/*
**	Changed the wall intersection technique to calculating the distance from
**		each wall, if it's less than the player->object->radius then block
**		movement
*/

int 	ft_get_intersecting_wall(t_linked_list *ws, t_point old,
		t_point new, double distance)
{
	t_wall		*wall;
	double		olddist;
	double		newdist;

	while (ws)
	{
		wall = ws->content;
		if (!(wall->properties & PROP_TRAVERSABLE))
		{
			olddist = ft_segment_distance_sq(old, wall->p1, wall->p2);
			newdist = ft_segment_distance_sq(new, wall->p1, wall->p2);
			if (newdist < distance && newdist < olddist)
				return (1);
		}
		ws = ws->next;
	}
	return (0);
}

/*
 * **	This function takes the player movement vector and applies wall resistance
 * **		on it
 * */

int		ft_wall_resistance(t_player *player)
{
	t_point	next_pos;

	next_pos.x = player->pos->x + player->speed.x;
	next_pos.y = player->pos->y + player->speed.y;
	if (ft_get_intersecting_wall(player->sector->walls.first,
				*(player->pos), next_pos, (player->object->radius *
					player->object->radius)))
	{
		player->speed.x = 0;
		player->speed.y = 0;
		player->zspeed = 0;
		return (1);
	}
	else
		return (0);
}

void	ft_apply_gravity(t_player *player, double delta_time)
{
	int	ceiling;
	int	floor;
	int	player_top;
	int	player_bottom;

	player->zspeed -= CONFIG_GRAVITY * delta_time;
	player->cam_height += player->zspeed;
	ceiling = player->sector->ceil_height + DEFAULT_WALLHEIGHT;
	floor = -player->sector->floor_height;
	player_top = player->cam_height + PLAYER_HEAD_MARGIN;
	player_bottom = player->cam_height -
		(player->height - player->crouch_height);
	if (player_bottom < floor)
	{
		player->cam_height = floor + player->height - player->crouch_height;
		player->zspeed = 0;
	}
	else if (player_top > ceiling)
	{
		player->cam_height = ceiling - PLAYER_HEAD_MARGIN;
		player->zspeed = 0;
	}
	if (player->crouch_height > 0)
		player->crouch_height -= PLAYER_CROUCH_SPEED * delta_time;
	else
		player->crouch_height = 0;
}

void	ft_player_behave(t_player *player, t_game *game)
{
	(void)game;
	ft_wall_resistance(player);
	ft_portal_traversal(player, player->object->radius *
				player->object->radius);
	ft_apply_gravity(player, game->delta_time);
}
