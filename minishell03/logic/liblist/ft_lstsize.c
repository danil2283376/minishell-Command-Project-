/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:38:17 by scolen            #+#    #+#             */
/*   Updated: 2021/02/21 11:13:28 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libminishell.h"

int		ft_lstsize(t_list *lst)
{
	unsigned int size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
