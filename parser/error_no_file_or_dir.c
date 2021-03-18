/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_no_file_or_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:58:18 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 14:58:29 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

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
