/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:32:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/16 20:02:05 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_command_not_found(t_obj *obj)
{
	errno = 127;
	write(2, "minishell : ", 12);
	write(2, obj->pars.command, ft_strlen(obj->pars.command));
	write(2, " : command not found\n", 21);
}

void	fn_numberic_argument_required(t_obj *obj)
{
	write(2, "minishell : ", 12);
	write(2, obj->pars.command, ft_strlen(obj->pars.command));
	write(2, ": ", 2);
	write(2, obj->pars.argument, ft_strlen(obj->pars.argument));
	write(2, ": numeric argument required\n", 28);
}

void	fn_too_many_arguments(t_obj *obj)
{
	errno = 1;
	write(2, "minishell : ", 12);
	write(2, obj->pars.command, ft_strlen(obj->pars.command));
	write(2, ": too many arguments\n", 21);
}

void	fn_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(errno);
}

void	fn_no_such_file(t_obj *obj)
{
	errno = 1;
	write(2, "minishell : ", 12);
	write(2, obj->pars.command, ft_strlen(obj->pars.command));
	write(2, ": ", 2);
	write(2, obj->pars.argument, ft_strlen(obj->pars.argument));
	write(2, ": No such file or directory\n", 28);
}

void	fn_not_a_directory(t_obj *obj)
{
	errno = 1;
	write(2, "minishell : ", 12);
	write(2, obj->pars.command, ft_strlen(obj->pars.command));
	write(2, ": ", 2);
	write(2, obj->pars.argument, ft_strlen(obj->pars.argument));
	write(2, ": Not a directory\n", 18);
}

void	fn_not_an_identifier(t_obj *obj, char *arg)
{
	write(2, "minishell : ", 12);
	write(2, obj->pars.command, ft_strlen(obj->pars.command));
	write(2, ": \'", 3);
	write(2, arg, ft_strlen(arg));
	write(2, "\': not a valid identifier\n", 26);
}