/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:03:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/13 16:18:16 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"
#include <stdio.h>

void	fn_check_pipe(t_obj *obj)
{
	int		i;

	i = 0;
	while (obj->pars.line[i])
	{
		if (obj->pars.line[i] == 124)
		{
			obj->flag.exist_pipe = 1;
			return ;
		}
		i++;
	}
}

void	fn_ctrl_c(int key)
{
	write(1, "\nminishell : ", 13);
	return ;
}

int		fn_check_before_redirect(t_obj *obj)
{
	int		i;
	char	ch;
	int		j;

	i = -1;
	while (obj->pars.line[++i])
	{
		ch = 'c';
		j = 0;
		if (obj->pars.line[i] == '\'' || obj->pars.line[i] == '\"')
		{
			ch = obj->pars.line[i];
			while (obj->pars.line[i] != ch && obj->pars.line[i])
				i++;
			if (obj->pars.line[i] == ch)
				i++;
		}
		if (obj->pars.line[i] == '\\')
			i+= 2;
		if (obj->pars.line[i] == '>' || obj->pars.line[i] == '<')
		{
			ch = obj->pars.line[i];
			while (obj->pars.line[i++] == ch)
				j++;
			if (j > 2)
				return (1);
			j = 0;
			i = fn_space(obj->pars.line, i);
			if (obj->pars.line[i] == ';')
			{
				while (obj->pars.line[i++] == ';')
					j++;
				if (j > 1)
					write(1, "minishell: syntax error near unexpected token ';;'\n", 51);
				else
					write(1, "minishell: syntax error near unexpected token ';'\n", 50);
				obj->flag.without_mistake = 1;
				return (0);
			}
			else if (obj->pars.line[i] == '|')
			{
				while (obj->pars.line[i++] == '|')
					j++;
				if (j > 1)
					write(1, "minishell: syntax error near unexpected token '||'\n", 51);
				else
					write(1, "minishell: syntax error near unexpected token '|'\n", 50);
				obj->flag.without_mistake = 1;
				return (0);
			}
		}
	}
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_obj	obj;
	int		i = 0;
	int		j;
	int		error;

	obj.standart_fd.fd_in = dup(0);
	obj.standart_fd.fd_out = dup(1);
	write(1, "minishell : ", 12);
	obj.pars.envp = envp;
	add_list_env(&obj.env_list, &obj.export_list ,obj.pars.envp);
	signal(2, fn_ctrl_c);
	signal(3, fn_ctrl_sl);
	error = 0;
	while ((get_next_line(&obj.pars.line, 0)) > 0)
	{
		j = 0;
		obj.pars.split_string = ft_split(obj.pars.line, ';');
		if (fn_check_before_redirect(&obj) != 0)
		{
			while (obj.pars.split_string[j] != NULL)
			{
				obj.flag.valid_com = 1;
				obj.pars.line = ft_strdup(obj.pars.split_string[j]);
				obj.flag.beg = 0;
				obj.flag.exist_pipe = 0;
				fn_check_pipe(&obj);
				if (obj.flag.exist_pipe == 0)
					fn_pars_line(&obj);
				else
				{
					i = 0;
					if (!(obj.pars.line_for_pipe = ft_split(obj.pars.line, 124)))
						fn_error("not memory allocate\n");
					while (obj.pars.line_for_pipe[i] != NULL)
						i++;
					obj.flag.p_flag.count_pipe = i; //КОЛИЧЕСТВО ПАЙПОВ БЛЯТЬ
					obj.pars.command_for_pipe = malloc(sizeof(char *) * (i + 2));
					obj.pars.command_for_pipe[i + 1] = NULL;
					obj.pars.argument_for_pipe = malloc(sizeof(char *) * (i + 2));
					obj.pars.argument_for_pipe[i + 1] = NULL;
					i = 0;
					while (obj.pars.line_for_pipe[i] != NULL)
					{
						obj.flag.beg = 0;
						obj.pars.line = ft_strdup(obj.pars.line_for_pipe[i]);
						if (fn_pars_line(&obj) == 0)
						{
							error = 1;
							break ;
						}
						obj.pars.command_for_pipe[i] = ft_strdup(obj.pars.command);
						obj.pars.argument_for_pipe[i] = ft_strdup(obj.pars.argument);
						i++;
					}
					if (error == 1)
						break ;
					if ((fn_process_for_pipes(&obj)) == 0)
						break ;
				}
				j++;
			}
		}
			write(1, "minishell : ", 12);
			free(obj.pars.line);
	}
	write(1, "\n", 1);
	return (0);
}
