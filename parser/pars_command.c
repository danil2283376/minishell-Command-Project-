/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:21:56 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 17:00:22 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		fn_search_redirect_com(t_obj *obj, int i)
{
	while (obj->pars.line[i] == '>' || obj->pars.line[i] == '<')
	{
		if (obj->pars.line[i] == '>')
			i = fn_redirect(obj);
		else
			i = fn_back_redirect(obj);
		if (i == -1)
			return (-1);
		i = fn_space(obj->pars.line, i);
	}
	return (i);
}

int		fn_pars_command_utils(t_obj *obj, int i)
{
	while (obj->pars.line[i] != ' ' && obj->pars.line[i] != ';'
	&& obj->pars.line[i] && obj->pars.line[i] != '>' &&
	obj->pars.line[i] != '<')
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
		else if (obj->pars.line[i] != '\0')
			i++;
		else
		{
			obj->flag.multiple_com = 0;
			return (-1);
		}
	}
	return (i);
}

void	fn_pars_command(t_obj *obj)
{
	int		i;
	int		redir;
	int		save;
	char	*leaks;

	i = obj->flag.beg;
	obj->flag.quote = '\0';
	obj->redirect.fd = 1;
	i = fn_search_redirect_com(obj, i);
	if (i == -1)
		return ;
	i = fn_pars_command_utils(obj, i);
	if (i == -1)
		return ;
	if (!(obj->pars.command = ft_substr(obj->pars.line,
	obj->flag.beg, i - obj->flag.beg)))
		fn_error("not memory allocate");
	leaks = obj->pars.command;
	obj->pars.command = fn_circumcision(obj->pars.command, obj);
	free(leaks);
	obj->flag.beg = i;
	fn_pars_argument(obj);
}
