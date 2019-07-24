/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:40:37 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 17:37:21 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_walls_draw(t_img *img, t_linked_list *walls, t_point offset)
{
	t_linked_list		*ws;
	t_wall				*wall;
	t_wall				temp_wall;

	ws = walls;
	while (ws)
	{
		wall = (t_wall *)ws->content;
		temp_wall = *wall;
		temp_wall.p1.x = temp_wall.p1.x / SCALE + offset.x;
		temp_wall.p1.y = temp_wall.p1.y / SCALE + offset.y;
		temp_wall.p2.x = temp_wall.p2.x / SCALE + offset.x;
		temp_wall.p2.y = temp_wall.p2.y / SCALE + offset.y;
		ft_sdl_draw_line(img, temp_wall.p1,  temp_wall.p2, 0xFF00FFFF);
		ws = ws->next;
	}
}

void	ft_portals_draw(t_img *img, t_linked_list *portals, t_point offset)
{
	t_linked_list		*p;
	t_wall				ws;
	t_portal			*portal;

	p = portals;
	while (p)
	{
		portal = (t_portal *)p->content;
		ws = portal->wall;
		ws.p1.x = ws.p1.x / SCALE + offset.x;
		ws.p1.y = ws.p1.y / SCALE + offset.y;
		ws.p2.x = ws.p2.x / SCALE + offset.x;
		ws.p2.y = ws.p2.y / SCALE + offset.y;
		ft_sdl_draw_line(img, ws.p1,  ws.p2, 0xFF00FFFF);
		p = p->next;
	}
}

void	ft_sectors_draw(t_img *img, t_sector *sect, Uint32 count, t_point offset)
{
	t_sector			p;
	int					i;

	i = -1;
	while (++i < count)
	{
		p = sect[i];
		ft_walls_draw(img, p.walls.first, offset);
		ft_portals_draw(img, p.portals.first, offset);
	}
}

void	ft_player_draw(t_img *img, t_player *p, t_point offset)
{
	t_point		pos;

	pos.x = offset.x + p->pos->x / SCALE;
	pos.y = offset.y + p->pos->y / SCALE;
	ft_memset(img->pixels, 0x00, sizeof(Uint32));
	ft_sdl_draw_disc(img, pos, 10, 0xFFFF00FF);
}

void	ft_edit_draw(t_env *e)
{
	ft_sdl_clear_pixels(e->e_img, 0xFFFFFF);
	ft_sectors_draw(e->e_img, e->game.sectors, e->game.sector_count, e->offset);
	ft_player_draw(e->e_img, e->game.main_player, e->offset);
}
