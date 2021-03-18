/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_back_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 08:48:50 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 18:30:41 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

int		fn_back_redirect(t_obj *obj)
{
	int		i;
	char	*leaks;

	i = init_param_back_redirect(obj);
	if (i == -1)
		return (-1);
	i = fn_space(obj->pars.line, obj->flag.beg);
	obj->flag.beg = fn_space(obj->pars.line, obj->flag.beg);
	if ((fn_check_error_with_back_redirect(obj)) == -1)
		return (-1);
	i = fn_after_error_back_redirect(obj, i);
	if (i == -1)
		return (-1);
	if (!(obj->pars.redirect = ft_substr(obj->pars.line,
	obj->flag.beg, i - obj->flag.beg)))
		fn_error("not memory allocate");
	leaks = obj->pars.redirect;
	obj->pars.redirect = fn_circumcision(obj->pars.redirect, obj);
	free(leaks);
	obj->redirect.fd_back_redirect = open(obj->pars.redirect, O_RDONLY, 0666);
	free(obj->pars.redirect);
	if (fn_zero_file(obj) == -1)
		return (-1);
	obj->flag.beg = fn_space(obj->pars.line, i);
	return (obj->flag.beg);
}
