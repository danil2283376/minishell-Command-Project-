/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_ec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:04:56 by melisha           #+#    #+#             */
/*   Updated: 2021/03/06 10:33:22 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

static	void	fn_check_flags(t_obj *obj)
{
	int		i;
	int		len;
	int		start;
	char	*new_arg;

	i = 0;
	start = 0;
	len = 0;
	new_arg = NULL;
	while (obj->pars.argument[i])
	{
		if (obj->pars.argument[i] == '-' && obj->pars.argument[i + 1] == 'n'
		&& (obj->pars.argument[i + 2] == ' ' || obj->pars.argument[i + 2] == '\0'))
			i+= 2;
		else
		{
			i++;
			len++;
		}
	}
	if (!(new_arg = (char *)malloc(sizeof(char) * (len + 1))))
		fn_error("not memory allocate");
	i = 0;
	len = 0;
	while (obj->pars.argument[i])
	{
		if (obj->pars.argument[i] == '-' && obj->pars.argument[i + 1] == 'n'
		&& (obj->pars.argument[i + 2] == ' ' || obj->pars.argument[i + 2] == '\0'))
		{
			obj->flag.c_flag.fl_ec = 1;
			i+= 2;
			i = fn_space(obj->pars.argument, i);
		}
		else
		{
			new_arg[len] = obj->pars.argument[i];
			i++;
			len++;
		}
	}
	new_arg[len] = '\0';
	obj->pars.argument = new_arg;
}

void	fn_valid_ec(t_obj *obj)
{
	fn_check_flags(obj);
	write(obj->redirect.fd, obj->pars.argument, ft_strlen(obj->pars.argument));
	if (obj->flag.c_flag.fl_ec == 0)
		write(obj->redirect.fd, "\n", 1);
}