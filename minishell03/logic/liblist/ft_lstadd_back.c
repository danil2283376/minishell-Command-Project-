/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:26:07 by scolen            #+#    #+#             */
/*   Updated: 2021/03/05 11:30:14 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libminishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *ptr;

	ptr = *lst;
	write(1, "1*", 2);
	if ((*lst) == NULL || lst == NULL)
	{
		*lst = new;
		return ;
	}
	write(1, "2*", 2);
	while ((ptr)->next != NULL)
		(ptr) = (ptr)->next;
	write(1, "3*", 2);
	(ptr)->next = new;
}
