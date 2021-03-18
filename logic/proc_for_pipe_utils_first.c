/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_for_pipe_utils_first.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:59:08 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 20:59:45 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

char	*ft_my_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	char			*ptr;
	unsigned int	start_ptr;
	unsigned int	start_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	start_ptr = 0;
	start_s = 0;
	ptr = (char *)malloc((len_s1 + len_s2) + 1);
	if (ptr == NULL)
		return (NULL);
	while (start_s < len_s1)
		ptr[start_ptr++] = s1[start_s++];
	start_s = 0;
	while (start_s < len_s2)
		ptr[start_ptr++] = s2[start_s++];
	ptr[start_ptr] = '\0';
	return (ptr);
}

void	free_double_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	search_path(t_obj *obj, t_command_varible_path *varible)
{
	char *new_str;

	while (varible->path[varible->j])
	{
		varible->k = varible->j;
		if (varible->j == -1)
			varible->j++;
		while (varible->path[varible->j] != ':' && varible->path[varible->j])
			varible->j++;
		if (varible->path[varible->j] == ':')
		{
			varible->path[varible->j] = '\0';
			varible->j++;
		}
		new_str = ft_strjoin(&varible->path[varible->k], "/");
		new_str = ft_strjoin(new_str, obj->pars.command);
		varible->error = execve(new_str, &varible->argv[0], obj->pars.envp);
		if (varible->error != -1)
			break ;
	}
}

void	path_null(t_obj *obj, t_command_varible_path *varible, int o)
{
	if (obj->redirect.fd_back_redirect != 0)
		obj->flag.exist_pipe = 0;
	if (!(varible->argv = ft_split(obj->pars.line_for_pipe[o], ' ')))
		fn_error("no memory allocate");
	obj->flag.exist_pipe = 1;
	search_path(obj, varible);
	if (varible->error == -1)
	{
		varible->error = execve(obj->pars.command,
		&varible->argv[0], obj->pars.envp);
		if (varible->error == -1)
			fn_command_not_found(obj);
	}
}

void	search_start(t_obj *obj, t_command_varible_path *varible, int o)
{
	if (!(obj->pars.line = ft_strdup(obj->pars.command_for_pipe[o])))
		fn_error("no memory allocate");
	obj->flag.beg = 0;
	fn_pars_line(obj);
	if (obj->redirect.fd_back_redirect != 0)
		dup2(obj->redirect.fd_back_redirect, 0);
	varible->j = 0;
	varible->path = fn_search_enviroment(obj, "PATH");
	if (varible->path != NULL)
		path_null(obj, varible, o);
	else
	{
		if (!(varible->argv = ft_split(obj->pars.line_for_pipe[o], ' ')))
			fn_error("no memory allocate");
		varible->error = execve(obj->pars.command,
		&varible->argv[0], obj->pars.envp);
		if (varible->error == -1)
			fn_command_not_found(obj);
	}
	obj->redirect.fd_back_redirect = 0;
}
