/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:52:53 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 17:50:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_env_display_mode(t_env *e)
{
	t_button	*p;

	if (e->in.mouse[SDL_BUTTON_LEFT])
	{
		p = e->buttons;
		while (p)
		{
			if (ft_mouse_on_button(p, e->in.mousex, e->in.mousey))
			{
				e->renderer_state = p->id;
				break ;
			}
			p = p->next;
		}
		if (e->in.mousex > E_START_X && e->in.mousey > E_START_Y && e->in.mousex < E_START_X + EDIT_W
				&& e->in.mousey < E_START_Y + E_START_Y + EDIT_H)
		{
			e->offset.x += e->in.mousexrel;
			e->offset.y += e->in.mouseyrel;
			e->in.mousexrel = 0;
			e->in.mouseyrel = 0;
		}
	}
}
