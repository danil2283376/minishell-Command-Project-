/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_for_pipe_utils_fird.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:02:20 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 21:02:39 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		threatment_pipe(t_obj *obj)
{
	t_threatment_pipe varible;

	varible.i = 0;
	varible.error = 0;
	varible.last_command = 0;
	while (varible.i < obj->flag.p_flag.count_pipe)
	{
		if (varible.i < obj->flag.p_flag.count_pipe - 1)
			pipe(varible.fd);
		if ((obj->pid = fork()) == 0)
			threatment_child_pipe(obj, &varible);
		else
			threatment_parrent_pipe(obj, &varible);
		obj->pid = 0;
		varible.i++;
	}
	dup2(obj->standart_fd.fd_in, 0);
	dup2(obj->standart_fd.fd_out, 1);
	obj->redirect.fd_back_redirect = 0;
	obj->redirect.fd = 1;
	return (1);
}

void	search_varible_in_path(t_obj *obj, t_process_for_pipes *varible)
{
	char *new_str;

	while (varible->path[varible->j])
	{
		varible->k = varible->j;
		if (varible->j == -1)
			varible->j++;
		while (varible->path[varible->j] != ':' &&
			varible->path[varible->j])
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

void	threatment_null_path(t_obj *obj, t_process_for_pipes *varible)
{
	varible->len = ft_strlen(varible->path);
	if (obj->redirect.fd_back_redirect != 0)
		obj->flag.exist_pipe = 0;
	obj->pars.line = fn_circumcision(obj->pars.line, obj);
	obj->flag.exist_pipe = 1;
	varible->argv = ft_split(obj->pars.line, ' ');
	search_varible_in_path(obj, varible);
	if (varible->error == -1)
	{
		varible->error = execve(obj->pars.command,
		&varible->argv[0], obj->pars.envp);
		if (varible->error == -1)
			fn_command_not_found(obj);
	}
}

void	threatment_child_solo_command(t_obj *obj, t_process_for_pipes *varible)
{
	varible->j = 0;
	varible->path = fn_search_enviroment(obj, "PATH");
	if (varible->path != NULL)
		threatment_null_path(obj, varible);
	else
	{
		varible->argv = ft_split(obj->pars.line, ' ');
		varible->error = execve(obj->pars.command,
		&varible->argv[0], obj->pars.envp);
		if (varible->error == -1)
			fn_command_not_found(obj);
	}
	exit(errno);
}

void	threament_fork_child(t_obj *obj, t_process_for_pipes *varible)
{
	int		status;

	if (obj->redirect.fd_back_redirect != 0)
		dup2(obj->redirect.fd_back_redirect, 0);
	varible->error = 0;
	if ((obj->pid = fork()) == 0)
		threatment_child_solo_command(obj, varible);
	else
	{
		waitpid(obj->pid, &status, 0);
		errno = WEXITSTATUS(status);
	}
}
