/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 10:52:41 by melisha           #+#    #+#             */
/*   Updated: 2021/03/05 10:17:41 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_ctrl_sl(int key)
{
	write(1, "Quit: 3\n", 9);
	return ;
}

int			ft_strlen_double_arr(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			threatment_command(t_obj *obj)
{
	char *new_str = "/bin/";
	int error;
	char **argv;
	pid_t pid;

	pid = fork();
	signal(3, fn_ctrl_sl);
	if (pid == 0)
	{
		if (!(argv = ft_split(obj->pars.line, ' ')))
			fn_error("not memory allocate");
		if (!(new_str = ft_strjoin(new_str, obj->pars.command)))
			fn_error("not memory allocate");
		error = execve(new_str, &argv[0], obj->pars.envp);
		if (error == -1)
			return (0);
	}
	else
		wait(&pid);
	return (1);
}

void		fn_error_processing(t_obj *obj)
{
	int		save;

	save = obj->flag.beg_for_pipe;
	obj->flag.beg_for_pipe = ft_strlen_double_arr(obj->pars.line_for_pipe);
	if (obj->pars.line[obj->flag.beg] == ';')
		write(1, "syntax error near unexpected token ';;'\n", 40);
	else if (obj->flag.valid_com == 0)
	{
		if (/*obj->flag.exist_pipe == 0 &&*/ (threatment_command(obj)) == 0)
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
	{
		if (obj->flag.exist_pipe == 0)
			fn_valid_arg(obj);
		obj->flag.beg_for_pipe = save;
	}
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
