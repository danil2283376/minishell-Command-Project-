/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:26:07 by scolen            #+#    #+#             */
/*   Updated: 2020/11/10 15:57:47 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *ptr;

	ptr = *lst;
	if ((*lst) == NULL || lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((ptr)->next != NULL)
		(ptr) = (ptr)->next;
	(ptr)->next = new;
}
