/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:08:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 13:16:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_sector_print(t_sector *sect, Uint32 count)
{
	t_sector			p;
	t_linked_list		*ws;
	t_wall				*wall;
	int					i;

	i = -1;
	while (++i < count)
	{
		printf("Sector : %d\n", i);
		p = sect[i];
		ws = p.walls.first;
		while (ws)
		{
			wall = (t_wall *)ws->content;
			printf("x1 : %d y1 : %d\t x2 : %d y2 : %d\n", wall->p1.x, wall->p1.y, wall->p2.x, wall->p2.y);
			ws = ws->next;
		}
	}
}
