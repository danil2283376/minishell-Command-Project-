/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 10:52:41 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 15:59:11 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		fn_error_processing(t_obj *obj)
{
	int		save;

	if (obj->flag.without_mistake == 1)
		obj->flag.beg = ft_strlen(obj->pars.line);
	else if (obj->pars.line[obj->flag.beg] == ';')
		write(2, "syntax error near unexpected token ';;'\n", 40);
	else if (obj->pars.line[obj->flag.beg] == '\0' && obj->pars.line[obj->flag.beg - 1] == ';' && fn_space(obj->pars.line, 0) == obj->flag.beg - 1)
		write(2, "syntax error near unexpected token ';'\n",39);
	else if (obj->flag.valid_redir == 0)
	{
		obj->flag.beg = ft_strlen(obj->pars.line);
		obj->redirect.count_red -= 2;
		if (obj->redirect.count_red == 0)
			write(2, "minishell : syntax error near unexpected token `>'\n", 51);
		else
			write(2, "minishell : syntax error near unexpected token `>>'\n", 52);
	}
	else if (obj->flag.valid_redir == -1)
	{
		write(2, "minishell : syntax error near unexpected token `newline'\n", 57);
		obj->flag.beg = ft_strlen(obj->pars.line);
	}
	else if (obj->flag.valid_back_red == -1)
	{
		write (2, "minishell: ", 11);
		write(2, obj->pars.redirect, ft_strlen(obj->pars.redirect));
		write(2, ": ", 2);
		perror(NULL);
		obj->flag.beg = ft_strlen(obj->pars.line);
	}
	else if (obj->flag.valid_back_red == 0)
	{
		obj->redirect.count_red -= 3;
		if (obj->redirect.count_red == 0)
			write(2, "minishell : syntax error near unexpected token `<'\n", 51);
		else if (obj->redirect.count_red == 1)
			write(2, "minishell : syntax error near unexpected token `<<'\n", 52);
		else
			write(2, "minishell : syntax error near unexpected token `<<<'\n", 53);
	}
	else if (obj->flag.multiple_com == 0)
	{
		write(1, "minishell : multiple commands are prohibited by subject\n", 56);
		obj->flag.beg = ft_strlen(obj->pars.line);
	}
	else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1)
		return (1);
	return (0);
}

void		fn_init_flags(t_obj *obj)
{
	obj->flag.c_flag.exp = 0;
	obj->flag.without_mistake = 0;
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

int		fn_pars_line(t_obj *obj)
{
	char	*leaks;

	leaks = obj->pars.line;
	obj->pars.line = ft_strtrim(obj->pars.line, " ");
	free(leaks);
	fn_check_environment_variable(obj);
	fn_init_flags(obj);
	obj->pars.arg_for_back_redirect = NULL;
	obj->pars.command = NULL;
	obj->pars.argument = NULL;
	fn_pars_command(obj);
	if (obj->pars.line[obj->flag.beg] == ';')
		obj->flag.beg++;
	if (fn_error_processing(obj) == 0)
		return (0);
	if (obj->flag.exist_pipe == 0)
		fn_process_for_pipes(obj);
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	return (1);
}
