/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:42:40 by melisha           #+#    #+#             */
/*   Updated: 2021/03/02 14:00:08 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		fn_redirect(t_obj *obj)
{
	int		i;

	obj->flag.beg += 1;
	i = fn_space(obj->pars.line, obj->flag.beg);
	obj->redirect.count_red = 0;
	while (obj->pars.line[i] == '>' && obj->pars.line[i] && obj->pars.line[i] != ';')
	{
		obj->redirect.count_red += 1;
		i++;
		obj->flag.beg++;
	}
	if (obj->redirect.count_red > 1)
	{
		obj->flag.valid_redir = 0;
		return (-1);
	}
	else if (obj->pars.line[i] == '\0')
	{
		obj->flag.valid_redir = -1;
		return (-1);
	}
	i = fn_space(obj->pars.line, obj->flag.beg);
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	while (obj->pars.line[i] != ' ' && obj->pars.line[i] != '\0' && obj->pars.line[i] != '>' && obj->pars.line[i] != ';')
	{
		if (obj->pars.line[i] == '\"' || obj->pars.line[i] == '\'')
		{
			obj->flag.quote = obj->pars.line[i];
			i++;
			while (obj->pars.line[i] != obj->flag.quote && obj->pars.line[i])
				i++;
		}
		if (obj->pars.line[i] != '\0')
			i++;
		else
		{
			obj->flag.multiple_com = 0;
			return (-1);
		}
	}
	if (!(obj->pars.redirect = ft_substr(obj->pars.line, obj->flag.beg, i - obj->flag.beg)))
		fn_error("not memory allocate");
	obj->pars.redirect = fn_circumcision(obj->pars.redirect, obj);
	printf("red = %s*\n", obj->pars.redirect);
	obj->flag.beg = fn_space(obj->pars.line, i);
	if (obj->redirect.count_red == 0)
		obj->redirect.fd = open(obj->pars.redirect, O_TRUNC | O_CREAT | O_RDWR, 0666);
	else if (obj->redirect.count_red == 1)
		obj->redirect.fd = open(obj->pars.redirect, O_RDWR | O_APPEND, 0666);
	return (obj->flag.beg);
}