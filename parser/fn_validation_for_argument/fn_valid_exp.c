/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:52:54 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 20:01:53 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void			exist_equal_continue1(t_obj *obj, t_export *export, int start)
{
	export->val = fn_search_enviroment(obj, export->name);
	if ((export->arg[export->j] == '\0' ||
	export->arg[export->j] == ' ') && export->val == NULL)
	{
		export_varible_in_env(&obj->export_list, export->name, "\n");
		export_varible_in_env(&obj->env_list, export->name, "\n");
	}
	else
	{
		start = export->j;
		while (export->arg[export->j] != '\0' && export->arg[export->j] != ' ')
			export->j++;
		if (!(export->value = ft_substr(export->arg, start, export->j - start)))
			fn_error("not memory allocate\n");
		export_varible_in_env(&obj->env_list, export->name, export->value);
		if (export->value[0] == '\"' || export->value[0] == '\'')
		{
			export->leaks = export->value;
			export->value = ft_strjoin("\\", export->value);
			free(export->leaks);
		}
		export_varible_in_env(&obj->export_list, export->name, export->value);
		free(export->value);
	}
	free(export->val);
}

void			exist_equal_continue(t_obj *obj, t_export *export)
{
	while (export->name[++export->k])
	{
		if ((export->name[export->k] <= '0' ||
		export->name[export->k] >= '9') &&
		export->name[export->k] && export->name[export->k] != '+')
			export->f = 1;
		else if ((export->name[export->k] >= '0' &&
		export->name[export->k] <= '9' && export->f != 1) ||
		export->name[export->k] == '+')
		{
			fn_not_an_identifier(obj, export->arg);
			free(export->arg);
			free(export->name);
			return ;
		}
	}
}

void			exist_equal(t_obj *obj, t_export *export, int start)
{
	if (export->j == 0)
	{
		free(export->arg);
		fn_not_an_identifier(obj, "=");
		return ;
	}
	if (!(export->name = ft_substr(export->arg, 0, export->j)))
		fn_error("not memory allocate\n");
	export->j++;
	export->k = -1;
	export->f = 0;
	exist_equal_continue(obj, export);
	exist_equal_continue1(obj, export, start);
}

static	void	fn_fill_val(t_obj *obj, int start, int i)
{
	t_export	export;

	export.j = 0;
	if (!(export.arg = ft_substr(obj->pars.argument, start, i - start)))
		fn_error("not memory allocate\n");
	while (export.arg[export.j] != ' ' && export.arg[export.j]
	!= '\0' && export.arg[export.j] != '=')
		export.j++;
	if (export.arg[export.j] == '=')
		exist_equal(obj, &export, start);
	else
		not_exist_equal(obj, &export, start);
	free(export.name);
	free(export.arg);
}

void			fn_valid_exp(t_obj *obj)
{
	char	*arg;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	if (obj->pars.argument[0] == '\0' ||
	obj->pars.argument[fn_space(obj->pars.argument, 0)] == '\0')
		sorting_export_list(&obj->export_list);
	else
	{
		while (obj->pars.argument[i] &&
		obj->pars.argument[fn_space(obj->pars.argument, i)])
		{
			if (obj->pars.argument[i] == ' ')
			{
				fn_fill_val(obj, start, i);
				i = fn_space(obj->pars.argument, i);
				start = i;
			}
			i++;
		}
		fn_fill_val(obj, start, i);
	}
}
