/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:22:29 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 20:23:11 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int				exist_value_env(t_list *list, char *value)
{
	t_list	*copy;
	int		i;
	char	*str;
	int		len_value;

	copy = list;
	i = 0;
	len_value = ft_strlen(value);
	while (copy->next != NULL)
	{
		copy = copy->next;
		str = (char *)copy->content;
		while (str[i] != '=' && str[i] && value[i])
		{
			if (str[i] == value[i])
				i++;
			else
				break ;
		}
		if (len_value == i)
			return (1);
		i = 0;
	}
	return (0);
}
