/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:51:57 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 22:04:15 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	unset_utils(t_list *before, t_list *after, int j, t_list *copy)
{
	int		k;

	k = 0;
	while (k != (j - 1))
	{
		before = before->next;
		k++;
	}
	if (before->next != NULL)
		before->next = after;
	free(copy->content);
	free(copy);
}

int		search_in_unset(t_list *copy, char *name_varible)
{
	int		i;
	char	*str;

	i = 0;
	str = copy->content;
	while (str[i] == name_varible[i] && str[i] != '\0' &&
	name_varible[i] != '\0')
		i++;
	return (i);
}

void	unset(t_list *env_list, char *name_varible)
{
	t_list	*copy;
	t_list	*before;
	t_list	*after;
	int		arr[4];
	int		boolean;

	copy = env_list;
	arr[1] = 0;
	arr[2] = ft_strlen(name_varible);
	boolean = exist_value_env(env_list, name_varible);
	if (boolean)
	{
		while (copy->next != NULL)
		{
			copy = copy->next;
			arr[0] = search_in_unset(copy, name_varible);
			if (arr[2] == arr[0])
				break ;
			arr[1]++;
		}
		after = copy->next;
		before = env_list->next;
		return (unset_utils(before, after, arr[1], copy));
	}
}
