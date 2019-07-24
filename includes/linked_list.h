/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:26:21 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:18:52 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef	struct		s_linked_list
{
	void					*content;
	struct s_linked_list	*next;
	struct s_linked_list	*prev;
}					t_linked_list;

typedef	struct		s_linked_list_head
{
	t_linked_list	*first;
	t_linked_list	*last;
}					t_linked_list_head;

t_linked_list		*ft_list_push(t_linked_list_head *head,
		t_linked_list *newnode);
void				ft_list_delete(t_linked_list_head *head,
		t_linked_list *element);
t_linked_list		*ft_list_newnode(void *content);
void				*ft_list_queue_pop(t_linked_list_head *head);
#endif
