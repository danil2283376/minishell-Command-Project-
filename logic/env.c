/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:35:39 by scolen            #+#    #+#             */
/*   Updated: 2021/03/18 20:23:06 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void			not_exist_varible(t_list *env_list,
	char *name_varible, char *value_varible)
{
	char *leaks;
	char *new_line;

	if (value_varible[0] == '\0')
	{
		new_line = ft_strdup(name_varible);
		ft_lstadd_back(&env_list, ft_lstnew(new_line));
	}
	else
	{
		new_line = ft_strjoin(name_varible, "=");
		if (*value_varible != '\n')
		{
			leaks = new_line;
			new_line = ft_strjoin(new_line, value_varible);
			free(leaks);
		}
		ft_lstadd_back(&env_list, ft_lstnew(new_line));
	}
}

int				exist_varible1(char *str, char *name_varible)
{
	int i;

	i = 0;
	while (str[i] != '=' && str[i] && name_varible[i])
	{
		if (str[i] == name_varible[i])
			i++;
		else
			break ;
	}
	return (i);
}

t_list			*take_before_list(t_list *env_list, int j)
{
	t_list	*copy_before;
	int		k;

	copy_before = env_list->next;
	k = 0;
	while (k != (j - 1))
	{
		copy_before = copy_before->next;
		k++;
	}
	return (copy_before);
}

void			exist_varible(t_varible_list varible_lists,
	t_list *env_list, char *new_line)
{
	char	*leaks;
	int		j;

	j = 0;
	while (varible_lists.copy->next != NULL)
	{
		varible_lists.copy = varible_lists.copy->next;
		if (varible_lists.len_value == exist_varible1(
			(char *)varible_lists.copy->content, varible_lists.name_varible))
		{
			varible_lists.current = varible_lists.copy;
			break ;
		}
		j++;
	}
	varible_lists.copy_after = varible_lists.copy->next;
	varible_lists.copy_before = take_before_list(env_list, j);
	free(varible_lists.current->content);
	free(varible_lists.copy);
	new_line = ft_strjoin(varible_lists.name_varible, "=");
	leaks = new_line;
	new_line = ft_strjoin(new_line, varible_lists.value_varible);
	free(leaks);
	varible_lists.copy_before->next = ft_lstnew(new_line);
	varible_lists.copy_before->next->next = varible_lists.copy_after;
}

void			export_varible_in_env(t_list *env_list,
	char *name_varible, char *value_varible)
{
	int				j;
	int				k;
	char			*leaks;
	t_varible_list	varible_lists;
	char			*new_line;

	varible_lists.len_value = ft_strlen(name_varible);
	varible_lists.copy = env_list;
	j = 0;
	k = 0;
	if (exist_value_env(env_list, name_varible))
	{
		varible_lists.name_varible = name_varible;
		varible_lists.value_varible = value_varible;
		exist_varible(varible_lists, env_list, new_line);
	}
	else
		not_exist_varible(env_list, name_varible, value_varible);
}
