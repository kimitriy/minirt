/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:23:45 by rburton           #+#    #+#             */
/*   Updated: 2021/01/24 02:07:37 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_el;

	new_el = (t_list *)malloc(1 * sizeof(t_list));
	if (NULL == new_el)
		return (NULL);
	new_el->content = content;
	new_el->next = NULL;
	return (new_el);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = (*lst);
	(*lst) = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (lst == NULL)
		return ;
	if ((*lst) == NULL)
	{
		(*lst) = new;
		new->next = NULL;
	}
	else
	{
		p = ft_lstlast(*lst);
		new->next = NULL;
		p->next = new;
	}
}

int		ft_lstsize(t_list *lst)
{
	int		i;

	if (lst == NULL)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}