/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_circumcision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:13:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 21:26:09 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

char	*fn_circumcision_fill(char *line, t_obj *obj, t_mass *mass)
{
	mass->i = -1;
	if (!(mass->com = (char *)malloc(sizeof(char) * (mass->len + 1))))
		fn_error("not memory allocate");
	mass->com[mass->len] = '\0';
	mass->len = 0;
	while (line[++mass->i])
	{
		if (line[mass->i] == ';')
			break ;
		if ((line[mass->i] == '>' || line[mass->i] == '<')
		&& obj->flag.exist_pipe == 0)
			mass->i = fn_circumcision_fill_red(line, mass->i);
		fn_circumcision_fill_utils(mass, line);
	}
	return (mass->com);
}

char	*fn_circumcision(char *line, t_obj *obj)
{
	t_mass	mass;

	mass.i = -1;
	mass.len = 0;
	while (line[++mass.i])
	{
		if (line[mass.i] == ';')
			break ;
		if ((line[mass.i] == '>' || line[mass.i] == '<')
		&& obj->flag.exist_pipe == 0)
			mass.i = fn_circumcision_count_red(line, mass.i);
		fn_circumcision_utils(line, &mass);
	}
	return (fn_circumcision_fill(line, obj, &mass));
}
