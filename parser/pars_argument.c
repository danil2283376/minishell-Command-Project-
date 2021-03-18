/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:21:43 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 17:25:44 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void			fn_insert_err_utils(int i, t_obj *obj)
{
	char	*save;
	char	*num;
	char	*leaks;

	leaks = obj->pars.argument;
	if (!(save = ft_strdup(obj->pars.argument)) ||
	!(obj->pars.argument =
	ft_substr(save, 0, i)) || !(num = ft_itoa(errno)))
		fn_error("not memory allocate");
	free(leaks);
	leaks = obj->pars.argument;
	if (!(obj->pars.argument = ft_strjoin(obj->pars.argument, num)))
		fn_error("not memory allocate");
	free(num);
	free(leaks);
	i += 2;
	if (save[i])
	{
		leaks = obj->pars.argument;
		if (!(obj->pars.argument =
		ft_strjoin(obj->pars.argument, &save[i])))
			fn_error("not memory allocate");
		free(leaks);
	}
}

static void		fn_insert_err(t_obj *obj)
{
	int		i;

	i = 0;
	while (obj->pars.argument[i] && obj->pars.argument[i] != '$')
		i++;
	if (obj->pars.argument[i] == '$' && obj->pars.argument[i + 1] == '?')
		fn_insert_err_utils(i, obj);
}

void			fn_pars_argument(t_obj *obj)
{
	int		i;
	int		redir;
	char	*leaks;

	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	i = obj->flag.beg;
	redir = 0;
	while (obj->pars.line[i] && obj->pars.line[i] != ';')
	{
		i = fn_pars_arg_utils(obj, i, redir);
		if (i == -1)
			return ;
		if (i == -2)
			break ;
	}
	if (!(obj->pars.argument =
	ft_substr(obj->pars.line, obj->flag.beg, i - obj->flag.beg)))
		fn_error("not memory allocate");
	leaks = obj->pars.argument;
	obj->pars.argument = fn_circumcision(obj->pars.argument, obj);
	free(leaks);
	fn_insert_err(obj);
	obj->flag.beg = i;
}
