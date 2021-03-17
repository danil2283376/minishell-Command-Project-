/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:21:43 by melisha           #+#    #+#             */
/*   Updated: 2021/03/16 14:16:25 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

static void		fn_insert_err(t_obj *obj)
{
	int		i;
	char	*save;
	char	*num;
	char	*leaks;

	i = 0;
	while (obj->pars.argument[i] && obj->pars.argument[i] != '$')
		i++;
	if (obj->pars.argument[i] == '$' && obj->pars.argument[i + 1] == '?')
	{
		leaks = obj->pars.argument;
		if (!(save = ft_strdup(obj->pars.argument)) ||
		!(obj->pars.argument = ft_substr(save, 0, i)) || !(num = ft_itoa(errno)))
			fn_error("not memory allocate");
		free(leaks);
		leaks = obj->pars.argument;
		if (!(obj->pars.argument = ft_strjoin(obj->pars.argument, num)))
			fn_error("not memory allocate");
		free(num);
		free(leaks);
		i+=2;
		if (save[i])
		{
			leaks = obj->pars.argument;
			if (!(obj->pars.argument = ft_strjoin(obj->pars.argument, &save[i])))
				fn_error("not memory allocate");
			free(leaks);
		}
	}
}

void	fn_pars_argument(t_obj *obj)
{
	int		i;
	int		redir;
	char	*leaks;

	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	i = obj->flag.beg;
	redir = 0;
	while (obj->pars.line[i] && obj->pars.line[i] != ';')
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
				return ;
			obj->flag.beg = redir;
		}
		if (obj->pars.line[i] == ';')
			break ;
		if (obj->pars.line[i] == '\"' || obj->pars.line[i] == '\'')
		{
			obj->flag.quote = obj->pars.line[i];
			i++;
			while (obj->pars.line[i] != obj->flag.quote && obj->pars.line[i])
				i++;
		}
		if (obj->pars.line[i] == '\\')
			i += 2;
		else if (obj->pars.line[i] != '\0' && obj->pars.line[i] != '>' && obj->pars.line[i] != '<')
			i++;
		else if (obj->pars.line[i] == '\0' && redir == 0)
		{
			obj->flag.multiple_com = 0;
			return ;
		}
	}
	if (!(obj->pars.argument = ft_substr(obj->pars.line, obj->flag.beg, i - obj->flag.beg)))
		fn_error("not memory allocate");
	leaks = obj->pars.argument;
	obj->pars.argument = fn_circumcision(obj->pars.argument, obj);
	free(leaks);
	fn_insert_err(obj);
	obj->flag.beg = i;
}