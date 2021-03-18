/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_check_before_redirect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:31:10 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 14:39:23 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int		dereferencing_before_redirect(t_obj *obj, int i)
{
	char	ch;

	ch = 0;
	if (obj->pars.line[i] == '\'' || obj->pars.line[i] == '\"')
	{
		ch = obj->pars.line[i];
		while (obj->pars.line[i] != ch && obj->pars.line[i])
			i++;
		if (obj->pars.line[i] == ch)
			i++;
	}
	if (obj->pars.line[i] == '\\')
		i += 2;
	return (i);
}

int		check_syntax_near_before_redirect(t_obj *obj, int i, int j)
{
	if (obj->pars.line[i] == ';')
	{
		while (obj->pars.line[i++] == ';')
			j++;
		if (j > 1)
			write(2, "minishell: syntax er\
ror near unexpected token ';;'\n", 51);
		else
			write(2, "minishell: syntax error near unexpected token ';'\n", 50);
		obj->flag.without_mistake = 1;
		return (-1);
	}
	else if (obj->pars.line[i] == '|')
	{
		while (obj->pars.line[i++] == '|')
			j++;
		if (j > 1)
			write(2, "minishell: syntax err\
or near unexpected token '||'\n", 51);
		else
			write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		obj->flag.without_mistake = 1;
		return (-1);
	}
	return (i);
}

int		fn_check_before_redirect(t_obj *obj)
{
	int		i;
	char	ch;
	int		j;

	i = -1;
	while (obj->pars.line[++i])
	{
		j = 0;
		i = dereferencing_before_redirect(obj, i);
		if (obj->pars.line[i] == '>' || obj->pars.line[i] == '<')
		{
			ch = obj->pars.line[i];
			while (obj->pars.line[i++] == ch)
				j++;
			if (j > 2)
				return (1);
			j = 0;
			i = fn_space(obj->pars.line, i);
			if ((i = check_syntax_near_before_redirect(obj, i, j)) == -1)
				return (0);
		}
	}
	return (1);
}
