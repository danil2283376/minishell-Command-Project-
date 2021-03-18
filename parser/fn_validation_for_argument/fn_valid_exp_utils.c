/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_exp_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:01:57 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 21:36:07 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

int			not_exist_equal(t_obj *obj, t_export *export, int start)
{
	(void)start;
	if (!(export->name = ft_substr(export->arg, 0, export->j)))
		fn_error("not memory allocate\n");
	export->k = -1;
	export->f = 0;
	while (export->name[++export->k])
	{
		if ((export->name[export->k] <= '0' ||
		export->name[export->k] >= '9') && export->name[export->k])
			export->f = 1;
		else if ((export->name[export->k] >= '0' &&
		export->name[export->k] <= '9' && export->f != 1) ||
		export->name[export->k] == '+')
		{
			free(export->name);
			fn_not_an_identifier(obj, export->arg);
			free(export->arg);
			return (-1);
		}
	}
	export->val = fn_search_enviroment(obj, export->name);
	if (export->val == NULL)
		export_varible_in_env(&obj->export_list, export->name, "\0");
	free(export->val);
	return (0);
}
