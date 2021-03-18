/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_un.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:56:11 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 20:41:18 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	fn_valid_arg_for_un(t_obj *obj, char *arg)
{
	int		i;
	int		f;

	i = 0;
	f = 0;
	while (arg[i])
	{
		if (((arg[i] < 65 || arg[i] > 90) && (arg[i] < 97 || arg[i] > 122)) || arg[i] == '=')
		{
			fn_not_an_identifier(obj, arg);
			f = 1;
			break ;
		}
		i++;
	}
	if (f == 0)
	{
		unset(&obj->env_list, arg);
		// unset(&obj->export_list, "__");
		unset(&obj->export_list, arg);
	}
	free(arg);
}

static void		fn_fill_val(t_obj *obj, char *arg, int start, int i)
{
	if (arg != NULL)
		free(arg);
	arg = ft_substr(obj->pars.argument, start, i - start);
	fn_valid_arg_for_un(obj, arg);
}

void	fn_valid_un(t_obj *obj)
{
	char	*arg;
	int		i;
	int		start;

	i = 0;
	start = 0;
	arg = NULL;
	while (obj->pars.argument[i] != '\0' && obj->pars.argument[fn_space(obj->pars.argument, i)])
	{
		if (obj->pars.argument[i] == ' ')
		{
			fn_fill_val(obj, arg, start, i);
			i = fn_space(obj->pars.argument, i);
			start = i;
		}
		i++;
	}
	fn_fill_val(obj, arg, start, i);
}