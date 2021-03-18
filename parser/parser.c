/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 10:52:41 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 15:03:36 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void		fn_init_flags(t_obj *obj)
{
	obj->flag.c_flag.exp = 0;
	obj->flag.without_mistake = 0;
	obj->flag.c_flag.fl_ec = 0;
	obj->flag.c_flag.envir = 0;
	obj->flag.c_flag.un = 0;
	obj->flag.c_flag.en = 0;
	obj->flag.c_flag.exi = 0;
	obj->flag.c_flag.cd = 0;
	obj->flag.c_flag.ec = 0;
	obj->flag.c_flag.pw = 0;
	obj->flag.valid_redir = 1;
	obj->flag.valid_back_red = 1;
	obj->flag.back_redirect = 0;
	obj->flag.multiple_com = 1;
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
}

int			fn_pars_line(t_obj *obj)
{
	char	*leaks;

	leaks = obj->pars.line;
	obj->pars.line = ft_strtrim(obj->pars.line, " ");
	free(leaks);
	fn_check_environment_variable(obj);
	fn_init_flags(obj);
	obj->pars.arg_for_back_redirect = NULL;
	obj->pars.command = NULL;
	obj->pars.argument = NULL;
	fn_pars_command(obj);
	if (obj->pars.line[obj->flag.beg] == ';')
		obj->flag.beg++;
	if (fn_error_processing(obj) == 0)
		return (0);
	if (obj->flag.exist_pipe == 0)
		fn_process_for_pipes(obj);
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	return (1);
}
