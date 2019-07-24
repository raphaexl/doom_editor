/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:11:36 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/24 10:16:15 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_button	*ft_button_new(SDL_Renderer	*rend, char	*msg, Uint32 color)
{
	t_button	*new;

	if (!(new = (t_button *)malloc(sizeof(t_button))))
		ft_printf("Error malloc in entry.c");
	new->color = color;
	new->text = ft_strdup(msg);
	new->pos = (SDL_Rect){0, 0, BUTTON_W, BUTTON_H};
	new->img = ft_get_render_text(rend, ft_font(msg, BUTTON_FONT, BUTTON_FSIZE),
						ft_sdl_color(color));
	new->ft_mouse_on = &ft_mouse_on_button;
	new->next = NULL;
	return (new);
}


void	ft_button_push_back(t_button **lst, t_button *new)
{
	t_button	*p;
	int			id;

	id = 1;
	if (!lst || !new)
		return ;
	else if (!*lst)
	{
		new->pos = (SDL_Rect){B_X_START, B_Y_START,  BUTTON_W, BUTTON_H};
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

void	ft_button_remove(t_button **lst, int id)
{
	t_button	*p;
	t_button	*q;

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

void	ft_button_clean(t_button **lst)
{
	t_button	*p;

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
