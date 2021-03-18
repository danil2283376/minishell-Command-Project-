/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:50:13 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 20:38:55 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void			output_export_list_utils(int quite, t_list *copy, int i)
{
	char	*str;

	str = (char *)(copy->content);
	write(1, "declare -x ", 11);
	while (str[i] != '=' && str[i])
		write(1, &str[i++], 1);
	if (str[i] == '=')
	{
		write(1, &str[i++], 1);
		write(1, "\"", 1);
	}
	else
		quite = 1;
	while (str[i])
		write(1, &str[i++], 1);
	if (quite == 0)
		write(1, "\"", 1);
	write(1, "\n", 1);
	i = 0;
}

void			output_export_list(t_list *export)
{
	t_list	*copy;
	int		i;
	char	*str;
	int		quite;

	copy = export->next;
	i = 0;
	quite = 0;
	while (copy != NULL)
	{
		output_export_list_utils(quite, copy, i);
		copy = copy->next;
	}
}

void			sorting_export_list(t_list *list)
{
	t_list	*copy;
	t_list	*next;
	char	*str[2];
	char	*tmp;

	copy = list->next;
	next = list->next->next;
	while (copy->next != NULL)
	{
		while (next->next != NULL)
		{
			str[0] = (char *)(copy->content);
			str[1] = (char *)(next->content);
			if (ft_strcmp(str[0], str[1]) > 0)
			{
				tmp = str[0];
				copy->content = str[1];
				next->content = tmp;
			}
			next = next->next;
		}
		copy = copy->next;
		next = copy;
	}
	output_export_list(list);
}
