/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:03:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/05 11:28:44 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"
#include <stdio.h>

void	fn_check_pipe(t_obj *obj)
{
	int		i;

	i = 0;
	while (obj->pars.line[i])
	{
		if (obj->pars.line[i] == 124)
		{
			obj->flag.exist_pipe = 1;
			return ;
		}
		i++;
	}
}

void	fn_ctrl_c(int key)
{
	write(1, "\nminishell : ", 13);
	return ;
}

int		main(int argc, char **argv, char **envp)
{
	t_obj	obj;
	int		i = 0;

	write(1, "minishell : ", 12);
	obj.pars.envp = envp;
	// write(1, "1", 1);
	add_list_env(&obj.env_list, &obj.export_list, obj.pars.envp);
	write(1, "2", 1);
	signal(2, fn_ctrl_c);
	signal(3, fn_ctrl_sl);
	while ((get_next_line(&obj.pars.line, 0)) > 0)
	{
		obj.flag.beg = 0;
		obj.flag.exist_pipe = 0;
		fn_check_environment_variable(&obj);
		fn_check_pipe(&obj);
		if (obj.flag.exist_pipe == 0)
			fn_pars_line(&obj);
		else
			fn_process_for_pipes(&obj);
		write(1, "minishell : ", 12);
		free(obj.pars.line);
	}
	write(1, "\n", 1);
	return (0);
}
