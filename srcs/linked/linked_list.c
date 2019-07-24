/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:39:24 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/22 21:17:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/editor.h"

t_linked_list	*ft_list_newnode(void *content)
{
	t_linked_list *result;

	result = malloc(sizeof(t_linked_list));
	if (!result)
	{
		ft_sdl_error("FT_SDL: Cannot allocate enough memory");
		return (NULL);
	}
	result->content = content;
	result->next = NULL;
	result->prev = NULL;
	return (result);
}

t_linked_list	*ft_list_push(t_linked_list_head *head, t_linked_list *newnode)
{
	static int init = 0;

	newnode->next = NULL;
	newnode->prev = NULL;
	if (!head->first || (init == 0))
		head->first = newnode;
	else
	{
		head->last->next = newnode;
		newnode->prev = head->last;
		newnode->next = NULL;
	}
	head->last = newnode;
	init = 1;
	return (newnode);
}

void			*ft_list_queue_pop(t_linked_list_head *head)
{
	t_linked_list	*target;
	void			*content;

	target = head->first;
	if (!target)
		return (NULL);
	head->first = target->next;
	if (head->last == target)
		head->last = NULL;
	content = target->content;
	free(target);
	return (content);
}

void			ft_list_delete(t_linked_list_head *head, t_linked_list *element)
{
	if (head->first == element)
		head->first = element->next;
	if (head->last == element)
		head->last = element->prev;
	if (head->last != element && head->first != element)
	{
		if (element->prev)
			element->prev->next = element->next;
		if (element->next)
			element->next->prev = element->prev;
	}
}
