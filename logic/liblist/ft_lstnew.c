/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:47:02 by scolen            #+#    #+#             */
/*   Updated: 2021/02/21 11:13:22 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libminishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list *list;

	list = malloc(1 * sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
