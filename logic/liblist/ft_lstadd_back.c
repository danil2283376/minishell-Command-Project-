/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:26:07 by scolen            #+#    #+#             */
/*   Updated: 2021/02/21 11:12:54 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libminishell.h"

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
