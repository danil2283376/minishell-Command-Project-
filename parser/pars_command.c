/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:21:56 by melisha           #+#    #+#             */
/*   Updated: 2021/03/06 10:25:54 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_pars_command(t_obj *obj)
{
	int		i;
	int		redir;
	int		save;

	i = obj->flag.beg;
	obj->flag.quote = '\0';
	obj->redirect.fd = 1;
	while ((obj->pars.line[i] == '>' || obj->pars.line[i] == '<') && obj->flag.exist_pipe == 0)
	{
		if (obj->pars.line[i] == '>')
			i = fn_redirect(obj);
		else
			i = fn_back_redirect(obj);
		if (i == -1)
			return ;
		i = fn_space(obj->pars.line, i);
	}
	while (obj->pars.line[i] != ' ' && obj->pars.line[i] != ';'
	&& obj->pars.line[i] && (obj->pars.line[i] != '>' || obj->flag.exist_pipe == 1))
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
			return ;
		}
	}
	if (!(obj->pars.command = ft_substr(obj->pars.line, obj->flag.beg, i - obj->flag.beg)))
		fn_error("not memory allocate");
	obj->pars.command = fn_circumcision(obj->pars.command, obj);
	obj->flag.beg = i;
	fn_pars_argument(obj);
}
