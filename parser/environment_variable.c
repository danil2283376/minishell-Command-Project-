/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:13:08 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 16:09:32 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

char	*fn_search_enviroment(t_obj *obj, char *name)
{
	int		i;
	char	*str;
	char	*value;
	t_list	*copy;

	copy = obj->env_list.next;
	while (copy)
	{
		i = 0;
		str = (char *)(copy->content);
		while (str[i] == name[i] && str[i] && name[i] && str[i] != '=')
			i++;
		if (i == ft_strlen(name))
		{
			i++;
			if (!(value = ft_substr(str, i, ft_strlen(str) - i)))
				fn_error("not memory allocate");
			return (value);
		}
		copy = copy->next;
	}
	return (NULL);
}

char	*fill_name(t_obj *obj, int i)
{
	char	*name;
	int		start;

	start = i;
	if (obj->pars.line[i] == ' ' || obj->pars.line[i] == '\0' || obj->pars.line[i] == '?')
		return (NULL);
	while (obj->pars.line[i] != ' ' && obj->pars.line[i] && obj->pars.line[i] != '=' && obj->pars.line[i] != '\"' && obj->pars.line[i] != '\'' && obj->pars.line[i] != '$')
		i++;
	if (!(name = ft_substr(obj->pars.line, start, i - start)))
		fn_error("not memory allocate");
	return (name);
}

void	fn_check_environment_variable(t_obj *obj)
{
	int		i;
	int		j;
	char	ch;
	char	*line;
	char	*name;
	char	*value;
	char	*leaks;
	char	*num;

	i = obj->flag.beg;
	j = 0;
	line = NULL;
	while (obj->pars.line[i] && obj->pars.line[i] != ';')
	{
		if (obj->pars.line[i] == '\'')
		{
			ch = obj->pars.line[i++];
			while (obj->pars.line[i] != ch && obj->pars.line[i])
				i++;
			i++;
		}
		if (obj->pars.line[i] == '$' && (obj->pars.line[i + 1] != ' ' && obj->pars.line[i + 1] != '\0') && obj->pars.line[i + 1] != '?' && obj->pars.line[i + 1] != '\\')
		{
			if (line != NULL)
			{
				leaks = line;
				num = ft_substr(obj->pars.line, j, i - j);
				line = ft_strjoin(line, num);
				free(num);
				free(leaks);
			}
			else
				line = ft_substr(obj->pars.line, j, i - j);
			name = fill_name(obj, i + 1);
			i+=1;
			if (name != NULL)
			{
				value = fn_search_enviroment(obj, name);
				if (value != NULL)
				{
					if (!line)
						line = ft_strdup(value);
					else
					{
						leaks = line;
						line = ft_strjoin(line, value);
						free(leaks);
					}
					free(value);
				}
				while (obj->pars.line[i] != ' ' && obj->pars.line[i] && obj->pars.line[i] != '=' && obj->pars.line[i] != '\"' && obj->pars.line[i] != '\'' && obj->pars.line[i] != '$')
					i++;
				j = i;
				free(name);
			}
		}
		else if (obj->pars.line[i] == '$' && obj->pars.line[i + 1] == '?')
		{
			if (line != NULL)
			{
				leaks = line;
				num = ft_substr(obj->pars.line, j, i - j);
				line = ft_strjoin(line, num);
				free(num);
				free(leaks);
			}
			else
				line = ft_substr(obj->pars.line, j, i - j);
			i+=2;
			j = i;
			if (!line)
			{
				num = ft_itoa(errno);
				line = ft_strdup(num);
				free(num);
			}
			else
			{
				leaks = line;
				num = ft_itoa(errno);
				line = ft_strjoin(line, num);
				free(num);
				free(leaks);
			}
			while (obj->pars.line[i] != ' ' && obj->pars.line[i])
						i++;
			if (i > j)
			{
				leaks = line;
				num = ft_substr(obj->pars.line, j, i - j);
				line = ft_strjoin(line, num);
				free(leaks);
			}
			j = i;
		}
		else if (obj->pars.line[i] == '$' && (obj->pars.line[i + 1] == ' ' || obj->pars.line[i + 1] == '\0' || obj->pars.line[i + 1] == '\\'))
			i+=1;
		if (obj->pars.line[i] != '$' && obj->pars.line[i])
			i+=1;
	}
	if (ft_strlen(obj->pars.line) > j)
	{
		leaks = line;
		line = ft_strjoin(line, &obj->pars.line[j]);
		free(leaks);
	}
	if (line != NULL)
	{
		leaks = obj->pars.line;
		obj->pars.line = ft_strdup(line);
		free(leaks);
		free(line);
	}
}