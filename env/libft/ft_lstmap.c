/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:35:57 by scolen            #+#    #+#             */
/*   Updated: 2020/11/07 16:57:57 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *ptr;
	t_list *new_list;

	if (lst == NULL)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	ptr = new_list;
	if (new_list == NULL)
		ft_lstclear(&lst, del);
	lst = lst->next;
	while (lst)
	{
		if (!(new_list->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&lst, del);
			break ;
		}
		lst = lst->next;
		new_list = new_list->next;
	}
	return (ptr);
}
