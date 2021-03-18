/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_error_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:02:52 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 15:16:44 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int			fn_error_processing(t_obj *obj)
{
	if (obj->flag.without_mistake == 1)
		obj->flag.beg = ft_strlen(obj->pars.line);
	else if (obj->pars.line[obj->flag.beg] == ';')
		write(2, "syntax error near unexpected token ';;'\n", 40);
	else if (obj->pars.line[obj->flag.beg] == '\0' &&
	obj->pars.line[obj->flag.beg - 1] == ';' &&
	fn_space(obj->pars.line, 0) == obj->flag.beg - 1)
		write(2, "syntax error near unexpected token ';'\n", 39);
	else if (obj->flag.valid_redir == 0)
		fn_error_valid_redir_zero(obj);
	else if (obj->flag.valid_redir == -1)
		fn_error_valid_redir_minus(obj);
	else if (obj->flag.valid_back_red == -1)
		fn_error_valid_back_redir_minus(obj);
	else if (obj->flag.valid_back_red == 0)
		fn_error_valid_back_redir_zero(obj);
	else if (obj->flag.multiple_com == 0)
		fn_error_mult_com(obj);
	else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1)
		return (1);
	return (0);
}
