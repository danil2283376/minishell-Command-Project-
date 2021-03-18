/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_circumcision_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:47:48 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 16:49:24 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_circumcision_utils(char *line, t_mass *mass)
{
	char	ch;

	while ((line[mass->i] == '\'' || line[mass->i] == '\"') && line[mass->i])
	{
		ch = line[mass->i];
		while (line[++mass->i] != ch && line[mass->i])
			mass->len++;
		mass->i++;
	}
	while (line[mass->i] == '\\')
		(mass->i += 2) != -1 ? mass->len += 1 : 0;
	if (line[mass->i] == ' ')
		(mass->len += 1) != -1 ? mass->i = fn_space(line, mass->len) - 1 : 0;
	else
		mass->len++;
}

int		fn_circumcision_fill_red(char *line, int i)
{
	char	ch;

	ch = line[i];
	while (line[i] == ch)
		i++;
	i = fn_space(line, i);
	while (line[i] != ' ' && line[i])
		i++;
	if (line[i] && line[i + 1] != ch)
		i++;
	return (i);
}

void	fn_circumcision_fill_utils(t_mass *mass, char *line)
{
	char	ch;

	while ((line[mass->i] == '\'' || line[mass->i] == '\"') && line[mass->i])
	{
		ch = line[mass->i];
		while (line[++mass->i] != ch && line[mass->i])
			mass->com[mass->len++] = line[mass->i];
		mass->i++;
	}
	while (line[mass->i] == '\\')
	{
		(mass->i++) != -1 ? mass->com[mass->len] = line[mass->i] : 0;
		(mass->len++) != -1 ? mass->i++ : 0;
	}
	if (line[mass->i] == ' ')
	{
		mass->com[mass->len++] = line[mass->i];
		mass->i = fn_space(line, mass->i) - 1;
	}
	else
		mass->com[mass->len++] = line[mass->i];
}

int		fn_circumcision_count_red(char *line, int i)
{
	char	ch;

	ch = line[i];
	while (line[i] == ch)
		i++;
	i = fn_space(line, i);
	while (line[i] != ' ' && line[i])
		i++;
	if (line[i] && line[i + 1] != ch)
		i++;
	return (i);
}
