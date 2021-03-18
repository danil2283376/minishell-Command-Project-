/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line_with_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:36:12 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 14:49:12 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int			begin_process_and_free(t_obj *obj)
{
	if ((fn_process_for_pipes(obj)) == 0)
		return (-1);
	free_double_array(obj->pars.command_for_pipe);
	free_double_array(obj->pars.line_for_pipe);
	free_double_array(obj->pars.argument_for_pipe);
	return (0);
}

int			fill_com_and_arg_in_pipes(t_obj *obj, int i, char *leaks)
{
	if (!(obj->pars.command_for_pipe = malloc(sizeof(char *) * (i + 1))))
		fn_error("no memory allocate");
	obj->pars.command_for_pipe[i] = NULL;
	if (!(obj->pars.argument_for_pipe = malloc(sizeof(char *) * (i + 1))))
		fn_error("no memory allocate");
	obj->pars.argument_for_pipe[i] = NULL;
	i = 0;
	while (obj->pars.line_for_pipe[i] != NULL)
	{
		obj->flag.beg = 0;
		leaks = obj->pars.line;
		obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
		free(leaks);
		if (fn_pars_line(obj) == 0)
			return (-1);
		obj->pars.command_for_pipe[i] = ft_strdup(obj->pars.command);
		free(obj->pars.command);
		obj->pars.argument_for_pipe[i] = ft_strdup(obj->pars.argument);
		free(obj->pars.argument);
		i++;
	}
	return (begin_process_and_free(obj));
}

int			pars_line_with_pipes(t_obj *obj)
{
	int		i;
	char	*leaks;

	i = 0;
	obj->pars.line_for_pipe = NULL;
	if (!(obj->pars.line_for_pipe = ft_split(obj->pars.line, '|')))
		fn_error("not memory allocate\n");
	while (obj->pars.line_for_pipe[i] != NULL)
	{
		leaks = obj->pars.line_for_pipe[i];
		obj->pars.line_for_pipe[i] =
		ft_strtrim(obj->pars.line_for_pipe[i], " ");
		free(leaks);
		i++;
	}
	obj->flag.p_flag.count_pipe = i;
	return (fill_com_and_arg_in_pipes(obj, i, leaks));
}
