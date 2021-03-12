/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:36:50 by melisha           #+#    #+#             */
/*   Updated: 2021/03/09 19:18:43 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

static void		fn_insert_err(t_obj *obj)
{
	int		i;
	char	*save;
	char	*num;

	i = 0;
	while (obj->pars.command[i] && obj->pars.command[i] != '$')
		i++;
	if (obj->pars.command[i] == '$' && obj->pars.command[i + 1] == '?')
	{
		if (!(save = ft_strdup(obj->pars.command)) ||
		!(obj->pars.command = ft_substr(save, 0, i)) || !(num = ft_itoa(errno)))
			fn_error("not memory allocate");
		if (!(obj->pars.command = ft_strjoin(obj->pars.command, num)))
			fn_error("not memory allocate");
		i+=2;
		if (save[i])
			if (!(obj->pars.command = ft_strjoin(obj->pars.command, &save[i])))
				fn_error("not memory allocate");
	}
}

int		utils_valid_command(t_obj *obj)
{
	if (obj->pars.command[0] == 'e' && obj->pars.command[1] == 'x' &&
	obj->pars.command[2] == 'p' && obj->pars.command[3] == 'o' &&
	obj->pars.command[4] == 'r' && obj->pars.command[5] == 't' &&
	obj->pars.command[6] == '\0' && (obj->flag.c_flag.exp = 1) != -1)
		return (1);
	if (obj->pars.command[0] == 'u' && obj->pars.command[1] == 'n' &&
	obj->pars.command[2] == 's' && obj->pars.command[3] == 'e' &&
	obj->pars.command[4] == 't' && obj->pars.command[5] == '\0' &&
	(obj->flag.c_flag.un = 1) != -1)
		return (1);
	if (obj->pars.command[0] == 'e' && obj->pars.command[1] == 'n' &&
	obj->pars.command[2] == 'v' && obj->pars.command[3] == '\0' &&
	(obj->flag.c_flag.en = 1) != -1)
		return (1);
	if (obj->pars.command[0] == '\0' &&
	obj->pars.line[fn_space(obj->pars.line, obj->flag.beg)] != '\'' &&
	obj->pars.line[fn_space(obj->pars.line, obj->flag.beg)] != '\"')
		return (1);
	else
		fn_insert_err(obj);
/*
** 	!minishell
*/
	return (0);
}

int		fn_valid_command(t_obj *obj)
{
	if (obj->pars.command[0] == 'e' && obj->pars.command[1] == 'x' &&
	obj->pars.command[2] == 'i' && obj->pars.command[3] == 't' &&
	obj->pars.command[4] == '\0' && (obj->flag.c_flag.exi = 1) != -1)
		return (1);
	if (((obj->pars.command[0] == 'e' && obj->pars.command[1] == 'c' &&
	obj->pars.command[2] == 'h' && obj->pars.command[3] == 'o' &&
	obj->pars.command[4] == '\0') || (obj->pars.command[0] == '/' && obj->pars.command[1] == 'b' &&
	obj->pars.command[2] == 'i' && obj->pars.command[3] == 'n' &&
	obj->pars.command[4] == '/' && obj->pars.command[5] == 'e' && obj->pars.command[6] == 'c' &&
	obj->pars.command[7] == 'h' && obj->pars.command[8] == 'o' &&
	obj->pars.command[9] == '\0')) && (obj->flag.c_flag.ec = 1) != -1)
		return (1);
	if (obj->pars.command[0] == 'c' && obj->pars.command[1] == 'd' &&
	obj->pars.command[2] == '\0' && (obj->flag.c_flag.cd = 1) != -1)
		return (1);
	if (((obj->pars.command[0] == 'p' && obj->pars.command[1] == 'w' &&
	obj->pars.command[2] == 'd' && obj->pars.command[3] == '\0') || (obj->pars.command[0] == '/' && obj->pars.command[1] == 'b' &&
	obj->pars.command[2] == 'i' && obj->pars.command[3] == 'n' &&
	obj->pars.command[4] == '/' && obj->pars.command[5] == 'p' && obj->pars.command[6] == 'w' &&
	obj->pars.command[7] == 'd' && obj->pars.command[8] == '\0')) &&
	(obj->flag.c_flag.pw = 1) != -1)
		return (1);
	return (utils_valid_command(obj));
}
