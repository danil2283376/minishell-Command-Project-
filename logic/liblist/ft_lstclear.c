/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:18:18 by scolen            #+#    #+#             */
/*   Updated: 2021/02/21 11:13:05 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libminishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if ((*lst)->next != NULL)
		ft_lstclear(&(*lst)->next, del);
	del((*lst)->content);
	free((*lst));
	(*lst) = NULL;
}
