/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_for_pipe_utils_second.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:00:47 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 21:01:12 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	search_command_varible_path(t_obj *obj, int o)
{
	t_command_varible_path	varible;

	varible.i = 0;
	varible.error = -1;
	varible.count = 0;
	obj->flag.exist_pipe = 0;
	if (!(obj->pars.line_for_pipe[o] =
		fn_circumcision(obj->pars.line_for_pipe[o], obj)))
		fn_error("no memory allocate");
	obj->flag.exist_pipe = 1;
	if (!(obj->pars.command = ft_strdup(obj->pars.command_for_pipe[o])))
		fn_error("no memory allocate");
	obj->flag.valid_com = fn_valid_command(obj);
	if (obj->flag.valid_com == 0 && obj->flag.after_redir != 1)
		search_start(obj, &varible, o);
	else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1)
	{
		if (!(obj->pars.argument = ft_strdup(obj->pars.argument_for_pipe[o])))
			fn_error("no memory allocate");
		fn_valid_arg(obj);
	}
}

int		fn_check_red(t_obj *obj, int i)
{
	int		j;

	j = 0;
	if (i != 0)
	{
		i--;
		while (obj->pars.line_for_pipe[i][j])
		{
			if (obj->pars.line_for_pipe[i][j] == '>')
				return (-1);
			j++;
		}
	}
	return (1);
}

void	threatment_child_pipe(t_obj *obj, t_threatment_pipe *varible)
{
	obj->pars.line = ft_strdup(
		obj->pars.line_for_pipe[varible->i]);
	fn_pars_line(obj);
	if (obj->redirect.fd != 1)
	{
		dup2(obj->redirect.fd, 1);
		close(varible->fd[0]);
		close(varible->fd[1]);
	}
	else
	{
		dup2(varible->fd[1], 1);
		close(varible->fd[0]);
		close(varible->fd[1]);
		if (obj->flag.after_redir != 1)
			search_command_varible_path(obj, varible->i);
	}
	exit(0);
}

void	threatment_redirect_in_pipe(t_obj *obj, t_threatment_pipe *varible)
{
	int		status;

	obj->flag.beg = 0;
	obj->flag.after_redir = 1;
	varible->leaks = obj->pars.line;
	obj->pars.line = ft_strdup(
		obj->pars.line_for_pipe[varible->i]);
	free(varible->leaks);
	obj->flag.exist_pipe = 0;
	fn_pars_line(obj);
	varible->leaks = obj->pars.line;
	obj->pars.line = fn_circumcision(obj->pars.line, obj);
	free(varible->leaks);
	varible->leaks = obj->pars.line_for_pipe[varible->i];
	obj->pars.line_for_pipe[varible->i] = ft_strdup(obj->pars.line);
	free(varible->leaks);
	obj->flag.exist_pipe = 1;
	dup2(obj->redirect.fd, 0);
	close(varible->fd[0]);
	close(varible->fd[1]);
	waitpid(obj->pid, &status, 0);
	errno = WEXITSTATUS(status);
}

void	threatment_parrent_pipe(t_obj *obj, t_threatment_pipe *varible)
{
	int		status;

	obj->flag.beg = 0;
	varible->leaks = obj->pars.line;
	obj->pars.line = ft_strdup(obj->pars.line_for_pipe[varible->i]);
	free(varible->leaks);
	fn_pars_line(obj);
	if (obj->pars.argument)
		free(obj->pars.argument);
	if (obj->pars.command)
		free(obj->pars.command);
	obj->flag.after_redir = 0;
	if (obj->redirect.fd != 1)
		threatment_redirect_in_pipe(obj, varible);
	else
	{
		dup2(varible->fd[0], 0);
		close(varible->fd[0]);
		close(varible->fd[1]);
		waitpid(obj->pid, &status, 0);
		errno = WEXITSTATUS(status);
	}
}
