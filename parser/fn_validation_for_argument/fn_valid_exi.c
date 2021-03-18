/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_exi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:03:01 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 19:15:31 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	start_exit(t_obj *obj, int *i, int check_first_time)
{
	*i = 0;
	while (obj->pars.argument[*i] && obj->pars.argument[*i] != ' ')
	{
		if ((obj->pars.argument[*i] == '+' || obj->pars.argument[*i] == '-')
		&& check_first_time == 0)
		{
			check_first_time = 1;
			i++;
		}
		if ((obj->pars.argument[*i] < '0' || obj->pars.argument[*i] > '9')
		&& obj->pars.argument[*i])
			obj->flag.c_flag.exi = 255;
		*i = *i + 1;
	}
	if (obj->flag.c_flag.exi == 255)
	{
		obj->pars.argument = ft_substr(obj->pars.argument, 0, *i);
		fn_numberic_argument_required(obj);
	}
}

void	fn_valid_exi(t_obj *obj)
{
	int			i;
	static	int	check_first_time = 0;

	i = 0;
	start_exit(obj, &i, check_first_time);
	if (obj->flag.c_flag.exi != 255 &&
	obj->pars.argument[fn_space(obj->pars.argument, i)] != '\0')
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
		errno = obj->flag.c_flag.exi;
		exit(obj->flag.c_flag.exi);
	}
}
