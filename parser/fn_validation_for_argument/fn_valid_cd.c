/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:03:40 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 20:18:45 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	goto_home(t_obj *obj, t_cd *varible_cd)
{
	varible_cd->save_arg = ft_strdup(obj->pars.argument);
	varible_cd->i = fn_space(obj->pars.argument, varible_cd->i) + 1;
	if (obj->pars.argument[varible_cd->i])
		varible_cd->home = ft_substr(obj->pars.argument,
			varible_cd->i, ft_strlen(obj->pars.argument) - varible_cd->i);
	else
		varible_cd->home = NULL;
	if (varible_cd->home == NULL)
	{
		varible_cd->leaks = obj->pars.argument;
		obj->pars.argument = fn_search_enviroment(obj, "HOME");
		free(varible_cd->leaks);
	}
	else
	{
		varible_cd->leaks = obj->pars.argument;
		varible_cd->pwd = fn_search_enviroment(obj, "HOME");
		obj->pars.argument = ft_strjoin(varible_cd->pwd, varible_cd->home);
		free(varible_cd->leaks);
		free(varible_cd->pwd);
	}
	free(varible_cd->home);
}

void	not_exist_file(t_obj *obj, t_cd *varible_cd, int fd)
{
	close(fd);
	fd = open(obj->pars.argument, O_RDONLY);
	if (fd == -1)
	{
		if (varible_cd->save_arg != NULL)
		{
			varible_cd->leaks = obj->pars.argument;
			obj->pars.argument = ft_strdup(varible_cd->save_arg);
			free(varible_cd->leaks);
		}
		fn_no_such_file(obj);
	}
	else
	{
		if (varible_cd->save_arg != NULL)
		{
			varible_cd->leaks = obj->pars.argument;
			obj->pars.argument = ft_strdup(varible_cd->save_arg);
			free(varible_cd->leaks);
		}
		fn_not_a_directory(obj);
	}
	close(fd);
}

void	change_directory(t_obj *obj, t_cd *varible_cd)
{
	int				fd;

	varible_cd->i = fn_space(obj->pars.argument, 0);
	varible_cd->len = varible_cd->i;
	while (obj->pars.argument[varible_cd->i] != ' '
		&& obj->pars.argument[varible_cd->i])
		varible_cd->i++;
	varible_cd->leaks = obj->pars.argument;
	if (!(obj->pars.argument = ft_substr(obj->pars.argument,
		varible_cd->len, varible_cd->i - varible_cd->len)))
		fn_error("no memory allocate");
	free(varible_cd->leaks);
	fd = open(obj->pars.argument, O_DIRECTORY);
	if (fd == -1)
		not_exist_file(obj, varible_cd, fd);
	else
		chdir(obj->pars.argument);
}

void	change_pwd_in_env(t_obj *obj, t_cd *varible_cd)
{
	varible_cd->value = fn_search_enviroment(obj, "PWD");
	if (varible_cd->value != NULL)
	{
		varible_cd->pwd = getcwd(NULL, 100000);
		export_varible_in_env(&obj->env_list, "PWD", varible_cd->pwd);
		export_varible_in_env(&obj->export_list, "PWD", varible_cd->pwd);
		free(varible_cd->pwd);
		export_varible_in_env(&obj->env_list, "OLDPWD", varible_cd->value);
		export_varible_in_env(&obj->export_list, "OLDPWD", varible_cd->value);
	}
	else
	{
		export_varible_in_env(&obj->env_list, "OLDPWD", "");
		export_varible_in_env(&obj->export_list, "OLDPWD", "");
	}
	if (varible_cd->save_arg)
		free(varible_cd->save_arg);
	free(varible_cd->value);
}

void	fn_valid_cd(t_obj *obj)
{
	t_cd	varible_cd;

	varible_cd.i = 0;
	varible_cd.save_arg = NULL;
	if (obj->pars.argument[varible_cd.i] &&
	obj->pars.argument[fn_space(obj->pars.argument, varible_cd.i)] == '~')
		goto_home(obj, &varible_cd);
	if (obj->pars.argument &&
	obj->pars.argument[fn_space(obj->pars.argument, varible_cd.i)] != '\0')
		change_directory(obj, &varible_cd);
	else
	{
		varible_cd.leaks = obj->pars.argument;
		obj->pars.argument = fn_search_enviroment(obj, "HOME");
		free(varible_cd.leaks);
		if (obj->pars.argument == NULL)
		{
			write(1, "minishell : cd: HOME not set\n", 29);
			if (varible_cd.save_arg)
				free(varible_cd.save_arg);
			return ;
		}
		chdir(obj->pars.argument);
	}
	change_pwd_in_env(obj, &varible_cd);
}
