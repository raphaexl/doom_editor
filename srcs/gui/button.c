/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:01:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:52:41 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int		ft_mouse_on_button(t_button *b, int x, int y)
{
	if ((x < b->pos.x) || (x > b->pos.x + b->pos.w) || (y < b->pos.y) || 
			(y > b->pos.y + b->pos.h))
		return (0);
	return (1);
}

void	ft_buttons_draw(t_env *e)
{
	t_button	*p;

	p = e->buttons;
	while (p)
	{
		SDL_RenderCopy(e->sdl.renderer, p->img, NULL, &p->pos);
		p = p->next;
	}
}
