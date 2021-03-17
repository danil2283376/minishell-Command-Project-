/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:52:54 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 14:26:15 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

static	void	fn_fill_val(t_obj *obj, int start, int i)
{
	char	*name;
	char	*value;
	char	*arg;
	char	ch;
	int		j;
	int		k;
	int		f;
	char	*leaks;
	char	*val;

	j = 0;
	if (!(arg = ft_substr(obj->pars.argument, start, i - start)))
		fn_error("not memory allocate\n");
	while (arg[j] != ' ' && arg[j] != '\0' && arg[j] != '=')
		j++;
	if (arg[j] == '=')
	{
		if (j == 0)
		{
			free(arg);
			fn_not_an_identifier(obj, "=");
			return ;
		}
		if (!(name = ft_substr(arg, 0, j)))
			fn_error("not memory allocate\n");
		j++;
		k = -1;
		f = 0;
		while (name[++k])
		{
			if ((name[k] <= '0' || name[k] >= '9') && name[k] && name[k] != '+')
				f = 1;
			else if ((name[k] >= '0' && name[k] <= '9' && f != 1) || name[k] == '+')
			{
				fn_not_an_identifier(obj, arg);
				free(arg);
				free(name);
				return ;
			}
		}
		val = fn_search_enviroment(obj, name);
		if ((arg[j] == '\0' || arg[j] == ' ') && val == NULL)
		{
			export_varible_in_env(&obj->export_list, name, "\n");
			export_varible_in_env(&obj->env_list, name, "\n");
		}
		else if (val != NULL)
		{
			free(val);
			return ;
		}
		else
		{
			start = j;
			while (arg[j] != '\0' && arg[j] != ' ')
				j++;
			if (!(value = ft_substr(arg, start, j - start)))
				fn_error("not memory allocate\n");
			export_varible_in_env(&obj->env_list, name, value);
			if (value[0] == '\"' || value[0] == '\'')
			{
				leaks = value;
				value = ft_strjoin("\\", value);
				free(leaks);
			}
			export_varible_in_env(&obj->export_list, name, value);
			free(value);
		}
		free(val);
	}
	else
	{
		if (!(name = ft_substr(arg, 0, j)))
			fn_error("not memory allocate\n");
		k = -1;
		f = 0;
		while (name[++k])
		{
			if ((name[k] <= '0' || name[k] >= '9') && name[k])
				f = 1;
			else if ((name[k] >= '0' && name[k] <= '9' && f != 1) || name[k] == '+')
			{
				free(name);
				fn_not_an_identifier(obj, arg);
				free(arg);
				return ;
			}
		}
		val = fn_search_enviroment(obj, name);
		if (val == NULL)
			export_varible_in_env(&obj->export_list, name, "\0");
		free(val);
	}
	free(name);
	free(arg);
}

void			fn_valid_exp(t_obj *obj)
{
	char	*arg;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	if (obj->pars.argument[0] == '\0' || obj->pars.argument[fn_space(obj->pars.argument, 0)] == '\0')
		sorting_export_list(&obj->export_list);
	else
	{
		while (obj->pars.argument[i] && obj->pars.argument[fn_space(obj->pars.argument, i)])
		{
			if (obj->pars.argument[i] == ' ')
			{
				fn_fill_val(obj, start, i);
				i = fn_space(obj->pars.argument, i);
				start = i;
			}
			i++;
		}
		fn_fill_val(obj, start, i);
	}
}