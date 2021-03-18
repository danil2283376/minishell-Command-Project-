/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:13:08 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 19:48:30 by melisha          ###   ########.fr       */
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
	if (obj->pars.line[i] == ' ' || obj->pars.line[i] == '\0'
	|| obj->pars.line[i] == '?')
		return (NULL);
	while (obj->pars.line[i] != ' ' && obj->pars.line[i] &&
	obj->pars.line[i] != '=' && obj->pars.line[i] != '\"' &&
	obj->pars.line[i] != '\'' && obj->pars.line[i] != '$')
		i++;
	if (!(name = ft_substr(obj->pars.line, start, i - start)))
		fn_error("not memory allocate");
	return (name);
}

void	penultimate_utils_check_env(t_obj *obj, t_env_var *var)
{
	if (obj->pars.line[var->i] == '$' && (obj->pars.line[var->i + 1] != ' '
	&& obj->pars.line[var->i + 1] != '\0') &&
	obj->pars.line[var->i + 1] != '?' && obj->pars.line[var->i + 1] != '\\')
	{
		second_utils_check_env(obj, var);
		third_utils_check_env(obj, var);
	}
	else if (obj->pars.line[var->i] == '$'
	&& obj->pars.line[var->i + 1] == '?')
	{
		fouth_utils_check_env(obj, var);
		fifth_utils_check_env(obj, var);
	}
	else if (obj->pars.line[var->i] == '$' &&
	(obj->pars.line[var->i + 1] == ' ' ||
	obj->pars.line[var->i + 1] == '\0' || obj->pars.line[var->i + 1] == '\\'))
		var->i += 1;
	if (obj->pars.line[var->i] != '$' && obj->pars.line[var->i])
		var->i += 1;
}

void	last_utils_check_env(t_obj *obj, t_env_var *var)
{
	if (ft_strlen(obj->pars.line) > var->j)
	{
		var->leaks = var->line;
		var->line = ft_strjoin(var->line, &obj->pars.line[var->j]);
		free(var->leaks);
	}
	if (var->line != NULL)
	{
		free(obj->pars.line);
		obj->pars.line = ft_strdup(var->line);
		free(var->line);
	}
}

void	fn_check_environment_variable(t_obj *obj)
{
	t_env_var	var;

	var.i = obj->flag.beg;
	var.j = 0;
	var.line = NULL;
	var.name = NULL;
	var.value = NULL;
	while (obj->pars.line[var.i] && obj->pars.line[var.i] != ';')
	{
		first_utils_check_env(obj, &var);
		penultimate_utils_check_env(obj, &var);
	}
	last_utils_check_env(obj, &var);
}
