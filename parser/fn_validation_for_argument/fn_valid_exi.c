/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_exi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:03:01 by melisha           #+#    #+#             */
/*   Updated: 2021/03/09 19:25:51 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	fn_valid_exi(t_obj *obj)
{
	int		i;
	static	int	check_first_time = 0;

	i = 0;
	while (obj->pars.argument[i] && obj->pars.argument[i] != ' ')
	{
		if ((obj->pars.argument[i] == '+' || obj->pars.argument[i] == '-') && check_first_time == 0)
		{
			check_first_time = 1;
			i++;
		}
		if ((obj->pars.argument[i] < '0' || obj->pars.argument[i] > '9') && obj->pars.argument[i])
			obj->flag.c_flag.exi = 255;
		i++;
	}
	if (obj->flag.c_flag.exi == 255)
	{
		obj->pars.argument = ft_substr(obj->pars.argument, 0, i);
		fn_numberic_argument_required(obj);
	}
	if (obj->flag.c_flag.exi != 255 && obj->pars.argument[fn_space(obj->pars.argument, i)] != '\0')
		fn_too_many_arguments(obj);
	else
	{
		if (obj->flag.c_flag.exi != 255)
		{
			obj->flag.c_flag.exi = ft_atoi(obj->pars.argument);
			if (obj->flag.c_flag.exi < 0)
				obj->flag.c_flag.exi = 255;
			else
			{
				while (obj->flag.c_flag.exi > 255)
					obj->flag.c_flag.exi -= 256;
			}
		}
		exit(obj->flag.c_flag.exi);
	}
}