/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:46:05 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 21:27:53 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fill_lists(t_list *env_list, t_list *export_list, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(envp[i])));
		ft_lstadd_back(&export_list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}

char	*return_value(t_list *env_list, t_list *export_list)
{
	t_list	*copy;
	char	*name;
	int		i;
	char	*key;
	char	*value;

	copy = env_list->next;
	name = ft_strdup("SHLVL");
	(void)export_list;
	while (copy)
	{
		i = 0;
		key = (char *)(copy->content);
		while (key[i] == name[i] && key[i] && name[i] && key[i] != '=')
			i++;
		if (i == ft_strlen(name))
		{
			i++;
			if (!(value = ft_substr(key, i, ft_strlen(key) - i)))
				fn_error("not memory allocate");
		}
		copy = copy->next;
	}
	free(name);
	return (value);
}

void	add_list_env(t_list *env_list, t_list *export_list, char **envp)
{
	char	*value;
	char	*leaks;

	fill_lists(env_list, export_list, envp);
	value = return_value(env_list, export_list);
	if (value != NULL)
	{
		leaks = value;
		value = (ft_itoa(ft_atoi(value) + 1));
		free(leaks);
		export_varible_in_env(env_list, "SHLVL", value);
		export_varible_in_env(export_list, "SHLVL", value);
		free(value);
	}
	else
	{
		export_varible_in_env(env_list, "SHLVL", "1");
		export_varible_in_env(export_list, "SHLVL", "1");
	}
}
