/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:55:30 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 10:33:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_sector	*ft_sector_new(SDL_Renderer	*rend, char	*msg, Uint32 color)
{
	t_sector	*new;

	if (!(new = (t_sector *)malloc(sizeof(t_sector))))
		ft_printf("Error malloc in sector");
	new->color = color;
	new->text = ft_strdup(msg);
	new->pos = (SDL_Rect){0, 0, sector_W, sector_H};
	new->img = ft_get_render_text(rend, ft_font(msg, sector_FONT, sector_FSIZE),
						ft_sdl_color(color));
	new->ft_mouse_on = &ft_mouse_on_sector;
	new->next = NULL;
	return (new);
}


void	ft_sector_push_back(t_sector **lst, t_sector *new)
{
	t_sector	*p;
	int			id;

	id = 1;
	if (!lst || !new)
		return ;
	else if (!*lst)
	{
		new->pos = (SDL_Rect){B_X_START, B_Y_START,  sector_W, sector_H};
		new->id = 0;
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next && ++id)
			p = p->next;
		new->pos = (SDL_Rect) {p->pos.x + p->pos.w + B_X_MARGIN, 
			p->pos.y +  B_Y_MARGIN, p->pos.w, p->pos.h};
		new->id = id;
		p->next = new;
	}
}

void	ft_sector_remove(t_sector **lst, int id)
{
	t_sector	*p;
	t_sector	*q;

	if (!lst || !*lst)
		return ;
	p = *lst;
	if (p && p->id == id)
	{
		*lst = (*lst)->next;
		free(p);
		return ;
	}
	q = (*lst)->next;
	while (q && q->id != id)
	{
		p = q;
		q = q->next;
	}
	if (q && q->id == id)
	{
		p->next = q->next;
		free(q);
		return ;
	}
}

void	ft_sector_clean(t_sector **lst)
{
	t_sector	*p;

	if (!lst || !*lst)
		return ;
	p = *lst;
	while (p)
	{
		(*lst) = (*lst)->next;
		free(p->text);
		free(p);
		p = (*lst);
	}
}
