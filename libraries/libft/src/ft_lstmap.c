/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:53:53 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/20 19:22:09 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_initialize(t_list **lst, void *(*f)(void *), void (*del)(void *),
		t_list **new_lst)
{
	t_list	*new_node;
	t_list	*new_content;

	while (*lst)
	{
		new_content = f((*lst)->content);
		if (!new_content)
		{
			ft_lstclear(new_lst, del);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(new_lst, new_node);
		*lst = (*lst)->next;
	}
	return (*new_lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;

	if (!lst || !f)
		return (NULL);
	new_lst = NULL;
	if (!ft_initialize(&lst, f, del, &new_lst))
		return (NULL);
	return (new_lst);
}
