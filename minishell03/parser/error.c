/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:32:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/13 13:32:29 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_command_not_found(t_obj *obj)
{
	errno = 127;
	write(1, "minishell : ", 12);
	write(1, obj->pars.command, ft_strlen(obj->pars.command));
	write(1, " : command not found\n", 21);
	exit(errno);
}

void	fn_numberic_argument_required(t_obj *obj)
{
	write(1, "minishell : ", 12);
	write(1, obj->pars.command, ft_strlen(obj->pars.command));
	write(1, ": ", 2);
	write(1, obj->pars.argument, ft_strlen(obj->pars.argument));
	write(1, ": numeric argument required\n", 28);
}

void	fn_too_many_arguments(t_obj *obj)
{
	errno = 1;
	write(1, "minishell : ", 12);
	write(1, obj->pars.command, ft_strlen(obj->pars.command));
	write(1, ": too many arguments\n", 21);
}

void	fn_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(errno);
}

void	fn_no_such_file(t_obj *obj)
{
	errno = 1;
	write(1, "minishell : ", 12);
	write(1, obj->pars.command, ft_strlen(obj->pars.command));
	write(1, ": ", 2);
	write(1, obj->pars.argument, ft_strlen(obj->pars.argument));
	write(1, ": No such file or directory\n", 28);
}

void	fn_not_a_directory(t_obj *obj)
{
	errno = 1;
	write(1, "minishell : ", 12);
	write(1, obj->pars.command, ft_strlen(obj->pars.command));
	write(1, ": ", 2);
	write(1, obj->pars.argument, ft_strlen(obj->pars.argument));
	write(1, ": Not a directory\n", 18);
}

void	fn_not_an_identifier(t_obj *obj, char *arg)
{
	write(1, "minishell : ", 12);
	write(1, obj->pars.command, ft_strlen(obj->pars.command));
	write(1, ": \'", 3);
	write(1, arg, ft_strlen(arg));
	write(1, "\': not a valid identifier\n", 26);
}