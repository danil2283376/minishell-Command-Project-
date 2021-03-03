/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:27:58 by scolen            #+#    #+#             */
/*   Updated: 2021/02/21 11:13:12 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libminishell.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	if (lst->next != NULL)
		ft_lstiter(lst->next, f);
	f(lst->content);
	lst = NULL;
}
