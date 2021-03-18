/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:52:26 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 12:57:52 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	utils_main(t_obj *obj)
{
	int		j;

	if (fn_check_before_redirect(obj) != 0)
	{
		j = 0;
		while (obj->pars.split_string[j] != NULL)
		{
			free(obj->pars.line);
			obj->pars.line = ft_strdup(obj->pars.split_string[j]);
			obj->flag.valid_com = 1;
			obj->flag.beg = 0;
			obj->flag.exist_pipe = 0;
			if ((fn_check_pipe(obj)) == -1)
				break ;
			if (obj->flag.exist_pipe == 0)
				fn_pars_line(obj);
			else if ((pars_line_with_pipes(obj)) == -1)
				break ;
			j++;
		}
		free_double_array(obj->pars.split_string);
	}
}
