/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:42:40 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 18:43:43 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		fn_after_init_param_redirect(t_obj *obj, int i)
{
	while (obj->pars.line[i] == '>' && obj->pars.line[i]
	&& obj->pars.line[i] != ';')
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
	else if (obj->pars.line[fn_space(obj->pars.line, i)] == '\0'
	&& obj->flag.exist_pipe == 0)
	{
		obj->flag.valid_redir = -1;
		return (-1);
	}
	return (i);
}

int		init_param_redirect(t_obj *obj)
{
	int		i;

	if (obj->redirect.fd != 1)
	{
		close(obj->redirect.fd);
		obj->redirect.fd = 1;
	}
	obj->flag.beg += 1;
	i = obj->flag.beg;
	obj->redirect.count_red = 0;
	return (fn_after_init_param_redirect(obj, i));
}

int		fn_after_error_redirect(t_obj *obj, int i)
{
	while (obj->pars.line[i] != ' ' && obj->pars.line[i] != '\0'
	&& obj->pars.line[i] != '>' && obj->pars.line[i] != ';')
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

void	fn_zero_file_redirect(t_obj *obj)
{
	if (obj->redirect.count_red == 0)
		obj->redirect.fd = open(obj->pars.redirect, O_TRUNC
		| O_CREAT | O_RDWR, 0666);
	else if (obj->redirect.count_red == 1)
	{
		obj->redirect.fd = open(obj->pars.redirect, O_RDWR | O_APPEND, 0666);
		if (obj->redirect.fd == -1)
			obj->redirect.fd = open(obj->pars.redirect, O_CREAT | O_RDWR, 0666);
	}
}

int		fn_redirect(t_obj *obj)
{
	int		i;
	char	*leaks;

	i = init_param_redirect(obj);
	if (i == -1)
		return (-1);
	i = fn_space(obj->pars.line, obj->flag.beg);
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	if ((fn_check_error_with_back_redirect(obj)) == -1)
		return (-1);
	i = fn_after_error_redirect(obj, i);
	if (i == -1)
		return (-1);
	if (!(obj->pars.redirect = ft_substr(obj->pars.line,
	obj->flag.beg, i - obj->flag.beg)))
		fn_error("not memory allocate");
	leaks = obj->pars.redirect;
	obj->pars.redirect = fn_circumcision(obj->pars.redirect, obj);
	free(leaks);
	obj->flag.beg = fn_space(obj->pars.line, i);
	fn_zero_file_redirect(obj);
	free(obj->pars.redirect);
	return (obj->flag.beg);
}
