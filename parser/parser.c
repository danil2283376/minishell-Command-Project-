/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 10:52:41 by melisha           #+#    #+#             */
/*   Updated: 2021/03/03 12:29:26 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"
// cat -e -t
int			threatment_command(t_obj *obj)
{
// 	char	*const* ad = "-e";
	//У тебя есть obj->pars.command = cat
	//И obj->pars.argument = ВСЁ ОСТАЛЬНОЕ, КРОМЕ ТОГО, ЧТО В КОМАНДЕ, ЯСНО ТЕБЕ?
	// if (obj->pars.command[0] == 'c' && obj->pars.command[1] == 'a' && obj->pars.command[2] == 't' && (obj->pars.command[3] == '\0' || obj->pars.command[fn_space(obj->pars.command, 3)] == '\0'))
		//CAT BLYAT;
	char *new_str = "/bin/";
	int error;
	char **argv;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		argv = ft_split(obj->pars.line, ' ');
		new_str = ft_strjoin(new_str, obj->pars.command);
		error = execve(new_str, &argv[0], obj->pars.envp);
	}
	else
		wait(&pid);
	return (1);
}

void		fn_error_processing(t_obj *obj)
{
	if (obj->pars.line[obj->flag.beg] == ';')
		write(1, "syntax error near unexpected token ';;'\n", 40);
	else if (obj->flag.valid_com == 0)
	{
		if ((threatment_command(obj)) == 0)
			fn_command_not_found(obj);
	}
	else if (obj->flag.valid_redir == 0)
	{
		obj->flag.beg = ft_strlen(obj->pars.line);
		obj->redirect.count_red -= 2;
		if (obj->redirect.count_red == 0)
			write(1, "minishell : syntax error near unexpected token `>'\n", 51);
		else
			write(1, "minishell : syntax error near unexpected token `>>'\n", 52);
	}
	else if (obj->flag.valid_redir == -1)
	{
		write(1, "minishell : syntax error near unexpected token `newline'\n", 57);
		obj->flag.beg = ft_strlen(obj->pars.line);
	}
	else if (obj->flag.valid_back_red == -1)
	{
		write (1, "minishell: ", 11);
		write(1, obj->pars.redirect, ft_strlen(obj->pars.redirect));
		write(1, ": ", 2);
		perror(NULL);
		obj->flag.beg = ft_strlen(obj->pars.line);
	}
	else if (obj->flag.valid_back_red == 0)
	{
		obj->redirect.count_red -= 3;
		if (obj->redirect.count_red == 0)
			write(1, "minishell : syntax error near unexpected token `<'\n", 51);
		else if (obj->redirect.count_red == 1)
			write(1, "minishell : syntax error near unexpected token `<<'\n", 52);
		else
			write(1, "minishell : syntax error near unexpected token `<<<'\n", 53);
	}
	else if (obj->flag.multiple_com == 0)
	{
		write(1, "minishell : multiple commands are prohibited by subject\n", 56);
		obj->flag.beg = ft_strlen(obj->pars.line);
	}
	else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1)
		fn_valid_arg(obj);
}

void		fn_init_flags(t_obj *obj)
{
	obj->flag.c_flag.exp = 0;
	obj->flag.c_flag.fl_ec = 0;
	obj->flag.c_flag.envir = 0;
	obj->flag.c_flag.un = 0;
	obj->flag.c_flag.en = 0;
	obj->flag.c_flag.exi = 0;
	obj->flag.c_flag.cd = 0;
	obj->flag.c_flag.ec = 0;
	obj->flag.c_flag.pw = 0;
	obj->flag.valid_redir = 1;
	obj->flag.valid_back_red = 1;
	obj->flag.back_redirect = 0;
	obj->flag.multiple_com = 1;
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
}

void		fn_pars_line(t_obj *obj)
{
	fn_init_flags(obj);
	obj->pars.arg_for_back_redirect = NULL;
	obj->pars.command = NULL;
	obj->pars.argument = NULL;
	fn_pars_command(obj);
	if (obj->pars.line[obj->flag.beg] == ';')
		obj->flag.beg++;
	if (obj->flag.exist_pipe == 0)
		fn_error_processing(obj);
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	if (obj->pars.line[obj->flag.beg] != '\0')
		fn_pars_line(obj);
}
