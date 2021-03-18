/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_for_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:59:03 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 21:02:37 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	threatment_our_command(t_obj *obj, t_process_for_pipes *varible)
{
	if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1)
		fn_valid_arg(obj);
	free(obj->pars.command);
	free(obj->pars.argument);
}

void	reset_fd(t_obj *obj)
{
	obj->flag.valid_com = fn_valid_command(obj);
	if (obj->redirect.fd != 1)
		dup2(obj->redirect.fd, 1);
}

int		close_fd(t_obj *obj)
{
	dup2(obj->standart_fd.fd_in, 0);
	dup2(obj->standart_fd.fd_out, 1);
	obj->redirect.fd = 1;
	return (1);
}

int		fn_process_for_pipes(t_obj *obj)
{
	t_process_for_pipes varible;

	varible.i = 0;
	if (obj->flag.exist_pipe == 1)
		threatment_pipe(obj);
	else
	{
		reset_fd(obj);
		if (obj->flag.valid_com == 0)
		{
			threament_fork_child(obj, &varible);
			if (varible.error == -1)
			{
				fn_command_not_found(obj);
				return (0);
			}
			if (obj->redirect.fd_back_redirect != 0)
				dup2(obj->standart_fd.fd_out, 0);
			obj->redirect.fd_back_redirect = 0;
			obj->flag.valid_com = 1;
			obj->pid = 0;
		}
		threatment_our_command(obj, &varible);
	}
	return (close_fd(obj));
}
