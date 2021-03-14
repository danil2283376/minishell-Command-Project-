/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:03:40 by melisha           #+#    #+#             */
/*   Updated: 2021/03/13 16:26:16 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	fn_valid_cd(t_obj *obj)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	if (obj->pars.argument && obj->pars.argument[fn_space(obj->pars.argument, i)] != '\0')
	{
		i = fn_space(obj->pars.argument, 0);
		len = i;
		while (obj->pars.argument[i] != ' ' && obj->pars.argument[i])
			i++;
		if (!(obj->pars.argument = ft_substr(obj->pars.argument, len, i - len)))
			fn_error("no memory allocate");
		int		fd;
		fd = open(obj->pars.argument, O_DIRECTORY);
		if (fd == -1)
		{
			fd = open(obj->pars.argument, O_RDONLY);
			if (fd == -1)
				fn_no_such_file(obj);
			else
				fn_not_a_directory(obj);
		}
		else
			chdir(obj->pars.argument);
	}
	else
	{
		obj->pars.argument = fn_search_enviroment(obj, "HOME");
		chdir(obj->pars.argument);
	}
	value = fn_search_enviroment(obj, "PWD");
	if (value != NULL)
	{
		export_varible_in_env(&obj->env_list, "PWD", getcwd(NULL, 100000));
		export_varible_in_env(&obj->export_list, "PWD", getcwd(NULL, 100000));
		export_varible_in_env(&obj->env_list, "OLDPWD", value);
		export_varible_in_env(&obj->export_list, "OLDPWD", value);
	}
	else
	{
		export_varible_in_env(&obj->env_list, "OLDPWD", "");
		export_varible_in_env(&obj->export_list, "OLDPWD", "");
	}
}
