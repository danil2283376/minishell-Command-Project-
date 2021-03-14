/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_circumcision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:13:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/03 14:09:16 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

char	*fn_circumcision_fill(char *line, int len, t_obj *obj)
{
	int		i;
	char	*com;
	char	ch;
	char	redch;

	i = -1;
	if (!(com = (char *)malloc(sizeof(char) * (len + 1))))
		fn_error("not memory allocate");
	com[len] = '\0';
	len = 0;
	while (line[++i])
	{
		if (line[i] == ';')
			break ;
		if ((line[i] == '>' || line[i] == '<') && obj->flag.exist_pipe == 0)
		{
			redch = line[i];
			while (line[i] == redch)
				i++;
			i = fn_space(line, i);
			while (line[i] != ' ' && line[i])
				i++;
			if (line[i] && line[i + 1] != redch)
				i++;
		}
		while ((line[i] == '\'' || line[i] == '\"') && line[i])
		{
			ch = line[i];
			while (line[++i] != ch && line[i])
				com[len++] = line[i];
			ch = 0;
			i++;
		}
		while (line[i] == '\\')
		{
			i++;
			com[len] = line[i];
			len++;
			i++;
		}
		if (line[i] == ' ')
		{
			com[len++] = line[i];
			i = fn_space(line, i) - 1;
		}
		else
			com[len++] = line[i];
	}
	free(line);
	return (com);
}

char	*fn_circumcision(char *line, t_obj *obj)
{
	int		i;
	int		len;
	char	ch;
	char	redch;

	i = -1;
	len = 0;
	while (line[++i])
	{
		if (line[i] == ';')
			break ;
		if ((line[i] == '>' || line[i] == '<') && obj->flag.exist_pipe == 0)
		{
			redch = line[i];
			while (line[i] == redch)
				i++;
			i = fn_space(line, i);
			while (line[i] != ' ' && line[i])
				i++;
			if (line[i] && line[i + 1] != redch)
				i++;
		}
		while ((line[i] == '\'' || line[i] == '\"') && line[i])
		{
			ch = line[i];
			while (line[++i] != ch && line[i])
				len++;
			ch = 0;
			i++;
		}
		while (line[i] == '\\')
		{
			i+=2;
			len+=1;
		}
		if (line[i] == ' ')
		{
			len += 1;
			i = fn_space(line, i) - 1;
		}
		else
			len++;
	}
	return(fn_circumcision_fill(line, len, obj));
}