/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envir_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:19:03 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 19:53:04 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	first_utils_check_env(t_obj *obj, t_env_var *var)
{
	if (obj->pars.line[var->i] == '\'')
	{
		var->ch = obj->pars.line[var->i++];
		while (obj->pars.line[var->i] != var->ch && obj->pars.line[var->i])
			var->i++;
		var->i++;
	}
}

void	second_utils_check_env(t_obj *obj, t_env_var *var)
{
	if (var->line != NULL)
	{
		var->leaks = var->line;
		var->num = ft_substr(obj->pars.line, var->j, var->i - var->j);
		var->line = ft_strjoin(var->line, var->num);
		free(var->num);
		free(var->leaks);
	}
	else
		var->line = ft_substr(obj->pars.line, var->j, var->i - var->j);
	var->leaks = var->name;
	var->name = fill_name(obj, var->i + 1);
	free(var->leaks);
	var->i += 1;
}

void	third_utils_check_env(t_obj *obj, t_env_var *var)
{
	if (var->name != NULL)
	{
		var->value = fn_search_enviroment(obj, var->name);
		if (var->value != NULL)
		{
			if (!var->line)
				var->line = ft_strdup(var->value);
			else
			{
				var->leaks = var->line;
				var->line = ft_strjoin(var->line, var->value);
				free(var->leaks);
			}
			free(var->value);
		}
		while (obj->pars.line[var->i] != ' ' && obj->pars.line[var->i] &&
		obj->pars.line[var->i] != '=' && obj->pars.line[var->i] != '\"'
		&& obj->pars.line[var->i] != '\'' && obj->pars.line[var->i] != '$')
			var->i++;
		var->j = var->i;
		free(var->name);
	}
}

void	fouth_utils_check_env(t_obj *obj, t_env_var *var)
{
	if (var->line != NULL)
	{
		var->leaks = var->line;
		var->num = ft_substr(obj->pars.line, var->j, var->i - var->j);
		var->line = ft_strjoin(var->line, var->num);
		free(var->num);
		free(var->leaks);
	}
	else
	{
		var->leaks = var->line;
		var->line = ft_substr(obj->pars.line, var->j, var->i - var->j);
		free(var->leaks);
	}
	var->i += 2;
	var->j = var->i;
}

void	fifth_utils_check_env(t_obj *obj, t_env_var *var)
{
	if (!var->line)
	{
		var->num = ft_itoa(errno);
		var->line = ft_strdup(var->num);
		free(var->num);
	}
	else
	{
		var->leaks = var->line;
		var->num = ft_itoa(errno);
		var->line = ft_strjoin(var->line, var->num);
		free(var->num);
		free(var->leaks);
	}
	while (obj->pars.line[var->i] != ' ' && obj->pars.line[var->i])
		var->i++;
	if (var->i > var->j)
	{
		var->num = ft_substr(obj->pars.line, var->j, var->i - var->j);
		var->leaks = var->line;
		var->line = ft_strjoin(var->line, var->num);
		free(var->num);
		free(var->leaks);
	}
	var->j = var->i;
}
