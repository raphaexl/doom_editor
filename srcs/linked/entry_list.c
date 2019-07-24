/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:56:40 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 10:13:26 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_entry			*ft_entry_new(SDL_Renderer	*rend, char	*msg, Uint32 color)
{
	t_entry	*new;

	if (!(new = (t_entry *)malloc(sizeof(t_entry))))
		ft_printf("Error malloc in entry");
	new->color = color;
	new->text = ft_strdup(msg);
	new->pos = (SDL_Rect){0, 0, entry_W, entry_H};
	new->img = ft_get_render_text(rend, ft_font(msg, entry_FONT, entry_FSIZE),
						ft_sdl_color(color));
	new->ft_mouse_on = &ft_mouse_on_entry;
	new->next = NULL;
	return (new);
}


void			ft_entry_push_back(t_entry **lst, t_entry *new)
{
	t_entry	*p;
	int			id;

	id = 1;
	if (!lst || !new)
		return ;
	else if (!*lst)
	{
		new->pos = (SDL_Rect){B_X_START, B_Y_START,  entry_W, entry_H};
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

void			ft_entry_remove(t_entry **lst, int id)
{
	t_entry	*p;
	t_entry	*q;

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

void			ft_entry_clean(t_entry **lst)
{
	t_entry	*p;

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
