/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:14:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 22:30:12 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int		fn_check_pipe_utils_two(t_obj *obj, int i)
{
	if (obj->pars.line[i] == '|')
	{
		write(2, "minishell : multiple com\
mands are prohibited by subject\n", 56);
		return (-1);
	}
	if (obj->pars.line[fn_space(obj->pars.line, i)] == '\0')
	{
		write(2, "minishell : multiple com\
mands are prohibited by subject\n", 56);
		return (-1);
	}
	obj->flag.exist_pipe = 1;
	return (i);
}

int		fn_check_pipe_utils(t_obj *obj, int i, int start)
{
	if (i == start)
	{
		while (obj->pars.line[i] == '|')
			i++;
		if (i - start > 1)
			write(2, "minishell: syn\
tax error near unexpected token `||'\n", 51);
		else
			write(2, "minishell: syn\
tax error near unexpected token `|'\n", 50);
		return (-1);
	}
	i++;
	return (fn_check_pipe_utils_two(obj, i));
}

int		fn_check_pipe(t_obj *obj)
{
	int		i;
	int		start;

	i = 0;
	start = fn_space(obj->pars.line, i);
	while (obj->pars.line[i])
	{
		if (obj->pars.line[i] == '|')
		{
			i = fn_check_pipe_utils(obj, i, start);
			if (i == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
