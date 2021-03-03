/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_ec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:04:56 by melisha           #+#    #+#             */
/*   Updated: 2021/03/03 11:33:48 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

static	void	fn_check_flags(t_obj *obj)
{
	int		i;
	int		start;
	char	*new_arg;

	i = -1;
	start = 0;
	new_arg = NULL;
	while (obj->pars.argument[++i])
	{
		if (obj->pars.argument[i] == '-' && obj->pars.argument[i + 1] == 'n' && (obj->pars.argument[i + 2] == ' ' || obj->pars.argument[i + 2] == '\0'))
			i+= 1;
		i++;
	}
}

void	fn_valid_ec(t_obj *obj)
{
	fn_check_flags(obj);
	write(obj->redirect.fd, obj->pars.argument, ft_strlen(obj->pars.argument));
	write(obj->redirect.fd, "\n", 1);
}