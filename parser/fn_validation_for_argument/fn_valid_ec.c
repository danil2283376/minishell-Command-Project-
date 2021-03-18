/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_ec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:04:56 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 19:08:14 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void			start_echo(t_obj *obj, t_echo *echo)
{
	echo->i = 0;
	echo->start = 0;
	echo->len = 0;
	echo->new_arg = NULL;
	while (obj->pars.argument[echo->i])
	{
		if ((echo->i == 0 || obj->pars.argument[echo->i - 1] == ' ')
			&& obj->pars.argument[echo->i] == '-'
			&& obj->pars.argument[echo->i + 1] == 'n'
			&& (obj->pars.argument[echo->i + 2] == ' '
			|| obj->pars.argument[echo->i + 2] == '\0'))
		{
			echo->i += 2;
			echo->i = fn_space(obj->pars.argument, echo->i);
		}
		else
		{
			echo->i++;
			echo->len++;
		}
	}
	if (!(echo->new_arg = (char *)malloc(sizeof(char) * (echo->len + 1))))
		fn_error("not memory allocate");
	echo->i = 0;
	echo->len = 0;
}

static	void	fn_check_flags(t_obj *obj)
{
	t_echo		echo;

	start_echo(obj, &echo);
	while (obj->pars.argument[echo.i])
	{
		if ((echo.i == 0 || obj->pars.argument[echo.i - 1] == ' ')
		&& obj->pars.argument[echo.i] == '-' &&
		obj->pars.argument[echo.i + 1] == 'n'
		&& (obj->pars.argument[echo.i + 2] == ' '
		|| obj->pars.argument[echo.i + 2] == '\0'))
		{
			obj->flag.c_flag.fl_ec = 1;
			echo.i += 2;
			echo.i = fn_space(obj->pars.argument, echo.i);
		}
		else
		{
			echo.new_arg[echo.len] = obj->pars.argument[echo.i];
			echo.i++;
			echo.len++;
		}
	}
	echo.new_arg[echo.len] = '\0';
	free(obj->pars.argument);
	obj->pars.argument = echo.new_arg;
}

void			fn_valid_ec(t_obj *obj)
{
	fn_check_flags(obj);
	write(obj->redirect.fd, obj->pars.argument, ft_strlen(obj->pars.argument));
	if (obj->flag.c_flag.fl_ec == 0)
		write(obj->redirect.fd, "\n", 1);
}
