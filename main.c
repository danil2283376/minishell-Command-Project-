/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:03:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 13:02:27 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

t_obj	obj;

void	s_ctr_sl(int sig)
{
	char	*num;

	if (obj.pid)
	{
		kill(obj.pid, sig);
		ft_putstr("Quit: ");
		num = ft_itoa(sig);
		ft_putstr(num);
		ft_putstr("\n");
	}
	else
		ft_putstr("\b\b  \b\b");
}

void	s_ctr_c(int key)
{
	if (key == SIGINT)
	{
		errno = 1;
		ft_putstr("\b\b  \b\b");
		write(1, "\nminishell : ", 13);
	}
}

int		main(int argc, char **argv, char **envp)
{
	int		j;

	obj.standart_fd.fd_in = dup(0);
	obj.standart_fd.fd_out = dup(1);
	write(1, "minishell : ", 12);
	obj.pars.envp = envp;
	add_list_env(&obj.env_list, &obj.export_list, obj.pars.envp);
	signal(SIGINT, s_ctr_c);
	signal(3, s_ctr_sl);
	while (1)
	{
		obj.pars.line = NULL;
		get_next_line(&obj.pars.line, 0);
		obj.pars.split_string = ft_split(obj.pars.line, ';');
		obj.flag.after_redir = 0;
		utils_main(&obj);
		write(1, "minishell : ", 12);
		free(obj.pars.line);
	}
	return (0);
}
