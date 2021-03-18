/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_argument_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:22:20 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 17:26:56 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		fn_pars_arg_utils_cont(t_obj *obj, int i, int redir)
{
	if (obj->pars.line[i] == '\"' || obj->pars.line[i] == '\'')
	{
		obj->flag.quote = obj->pars.line[i];
		i++;
		while (obj->pars.line[i] != obj->flag.quote && obj->pars.line[i])
			i++;
	}
	if (obj->pars.line[i] == '\\')
		i += 2;
	else if (obj->pars.line[i] != '\0' && obj->pars.line[i] != '>'
	&& obj->pars.line[i] != '<')
		i++;
	else if (obj->pars.line[i] == '\0' && redir == 0)
	{
		obj->flag.multiple_com = 0;
		return (-1);
	}
	return (i);
}

int		fn_pars_arg_utils(t_obj *obj, int i, int redir)
{
	while (obj->pars.line[i] == '>' || obj->pars.line[i] == '<')
	{
		redir = obj->flag.beg;
		obj->flag.beg = i;
		if (obj->pars.line[i] == '>')
			i = fn_redirect(obj);
		else
			i = fn_back_redirect(obj);
		if (i == -1)
			return (-1);
		obj->flag.beg = redir;
	}
	if (obj->pars.line[i] == ';')
		return (-2);
	return (fn_pars_arg_utils_cont(obj, i, redir));
}
