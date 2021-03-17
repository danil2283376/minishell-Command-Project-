/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:03:40 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 17:13:45 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	fn_valid_cd(t_obj *obj)
{
	int		i;
	int		len;
	int		start;
	char	*value;
	char	*home;
	char	*pwd;
	char	*save_arg;
	char	*leaks;

	i = 0;
	save_arg = NULL;
	if (obj->pars.argument[i] && obj->pars.argument[fn_space(obj->pars.argument, i)] == '~')
	{
		save_arg = ft_strdup(obj->pars.argument);
		i = fn_space(obj->pars.argument, i) + 1;
		if (obj->pars.argument[i])
			home = ft_substr(obj->pars.argument, i, ft_strlen(obj->pars.argument) - i);
		else
			home = NULL;
		if (home == NULL)
		{
			leaks = obj->pars.argument;
			obj->pars.argument = fn_search_enviroment(obj, "HOME");
			free(leaks);
		}
		else
		{
			leaks = obj->pars.argument;
			pwd = fn_search_enviroment(obj, "HOME");
			obj->pars.argument = ft_strjoin(pwd, home);
			free(leaks);
			free(pwd);
			free(home);
		}
	}
	if (obj->pars.argument && obj->pars.argument[fn_space(obj->pars.argument, i)] != '\0')
	{
		i = fn_space(obj->pars.argument, 0);
		len = i;
		while (obj->pars.argument[i] != ' ' && obj->pars.argument[i])
			i++;
		leaks = obj->pars.argument;
		if (!(obj->pars.argument = ft_substr(obj->pars.argument, len, i - len)))
			fn_error("no memory allocate");
		free(leaks);
		int		fd;
		fd = open(obj->pars.argument, O_DIRECTORY);
		if (fd == -1)
		{
			close(fd);
			fd = open(obj->pars.argument, O_RDONLY);
			if (fd == -1)
			{
				if (save_arg != NULL)
				{
					leaks = obj->pars.argument;
					obj->pars.argument = ft_strdup(save_arg);
					free(leaks);
				}
				fn_no_such_file(obj);
			}
			else
			{
				if (save_arg != NULL)
				{
					leaks = obj->pars.argument;
					obj->pars.argument = ft_strdup(save_arg);
					free(leaks);
				}
				fn_not_a_directory(obj);
			}
			close(fd);
		}
		else
			chdir(obj->pars.argument);
	}
	else
	{
		leaks = obj->pars.argument;
		obj->pars.argument = fn_search_enviroment(obj, "HOME");
		free(leaks);
		if (obj->pars.argument == NULL)
		{
			write(1, "minishell : cd: HOME not set\n", 29);
			return ;
		}
		chdir(obj->pars.argument);
	}
	value = fn_search_enviroment(obj, "PWD");
	if (value != NULL)
	{
		pwd = getcwd(NULL, 100000);
		export_varible_in_env(&obj->env_list, "PWD", pwd);
		export_varible_in_env(&obj->export_list, "PWD", pwd);
		free(pwd);
		export_varible_in_env(&obj->env_list, "OLDPWD", value);
		export_varible_in_env(&obj->export_list, "OLDPWD", value);
	}
	else
	{
		export_varible_in_env(&obj->env_list, "OLDPWD", "");
		export_varible_in_env(&obj->export_list, "OLDPWD", "");
	}
	if (save_arg)
		free(save_arg);
	free(value);
}
