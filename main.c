/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:03:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 14:53:12 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

t_obj	g_obj;

void	s_ctr_sl(int sig)
{
	char	*num;

	if (g_obj.pid)
	{
		kill(g_obj.pid, sig);
		ft_putstr("Quit: ");
		num = ft_itoa(sig);
		ft_putstr(num);
		ft_putstr("\n");
		free(num);
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

	g_obj.standart_fd.fd_in = dup(0);
	g_obj.standart_fd.fd_out = dup(1);
	write(1, "minishell : ", 12);
	g_obj.pars.envp = envp;
	add_list_env(&g_obj.env_list, &g_obj.export_list, g_obj.pars.envp);
	signal(SIGINT, s_ctr_c);
	signal(3, s_ctr_sl);
	while (1)
	{
		g_obj.pars.line = NULL;
		get_next_line(&g_obj.pars.line, 0);
		g_obj.pars.split_string = ft_split(g_obj.pars.line, ';');
		g_obj.flag.after_redir = 0;
		utils_main(&g_obj);
		write(1, "minishell : ", 12);
		free(g_obj.pars.line);
	}
	return (0);
}
