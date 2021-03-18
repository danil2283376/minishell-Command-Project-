/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_back_redirect_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:30:21 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 18:38:02 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		fn_after_init_param_back_redirect(t_obj *obj, int i)
{
	while (obj->pars.line[i] == '<' && obj->pars.line[i]
	&& obj->pars.line[i] != ';')
	{
		obj->redirect.count_red += 1;
		i++;
		obj->flag.beg++;
	}
	if (obj->redirect.count_red > 1)
	{
		obj->flag.valid_back_red = 0;
		return (-1);
	}
	else if (obj->pars.line[i] == '\0')
	{
		obj->flag.valid_redir = -1;
		return (-1);
	}
	return (i);
}

int		init_param_back_redirect(t_obj *obj)
{
	int		i;

	if (obj->redirect.fd_back_redirect != 0)
	{
		close(obj->redirect.fd_back_redirect);
		obj->redirect.fd_back_redirect = 0;
	}
	obj->flag.beg += 1;
	obj->flag.back_redirect = 1;
	i = obj->flag.beg;
	obj->redirect.count_red = 0;
	return (fn_after_init_param_back_redirect(obj, i));
}

int		fn_check_error_with_back_redirect(t_obj *obj)
{
	if (obj->pars.line[obj->flag.beg] == '<')
	{
		obj->redirect.count_red = 1;
		while (obj->pars.line[obj->flag.beg] == '<')
		{
			obj->flag.beg++;
			obj->redirect.count_red++;
		}
		obj->flag.valid_back_red = 0;
		return (-1);
	}
	else if (obj->pars.line[obj->flag.beg] == '>')
	{
		obj->redirect.count_red = 1;
		while (obj->pars.line[obj->flag.beg] == '>')
		{
			obj->flag.beg++;
			obj->redirect.count_red += 1;
		}
		obj->flag.valid_redir = 0;
		return (-1);
	}
	return (0);
}

int		fn_after_error_back_redirect(t_obj *obj, int i)
{
	while (obj->pars.line[i] != ' ' && obj->pars.line[i] != '\0'
	&& obj->pars.line[i] != '<' && obj->pars.line[i] != ';')
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
	return (i);
}

int		fn_zero_file(t_obj *obj)
{
	if (obj->redirect.fd_back_redirect == -1)
	{
		obj->flag.valid_back_red = -1;
		return (-1);
	}
	if (obj->redirect.count_red == 1)
	{
		obj->flag.multiple_com = 0;
		return (-1);
	}
	return (0);
}
