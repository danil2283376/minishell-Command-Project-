/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:03:19 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 17:55:09 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libminishell.h"
t_obj	obj;

int		fn_check_pipe(t_obj *obj)
{
	int		i;
	int		start;

	i = 0;
	start = fn_space(obj->pars.line, i);
	while (obj->pars.line[i])
	{
		if (obj->pars.line[i] == '|')
		{
			if (i == start)
			{
				while (obj->pars.line[i] == '|')
					i++;
				if (i - start > 1)
					write(2, "minishell: syntax error near unexpected token `||'\n", 51);
				else
					write(2, "minishell: syntax error near unexpected token `|'\n", 50);
				return (-1);
			}
			i++;
			if (obj->pars.line[i] == '|')
			{
				write(2, "minishell : multiple commands are prohibited by subject\n", 56);
				return (-1);
			}
			if (obj->pars.line[fn_space(obj->pars.line, i)] == '\0')
			{
				write(2, "minishell : multiple commands are prohibited by subject\n", 56);
				return (-1);
			}
			obj->flag.exist_pipe = 1;
		}
		i++;
	}
	return (0);
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
					write(2, "minishell: syntax error near unexpected token ';;'\n", 51);
				else
					write(2, "minishell: syntax error near unexpected token ';'\n", 50);
				obj->flag.without_mistake = 1;
				return (0);
			}
			else if (obj->pars.line[i] == '|')
			{
				while (obj->pars.line[i++] == '|')
					j++;
				if (j > 1)
					write(2, "minishell: syntax error near unexpected token '||'\n", 51);
				else
					write(2, "minishell: syntax error near unexpected token '|'\n", 50);
				obj->flag.without_mistake = 1;
				return (0);
			}
		}
	}
	return (1);
}

int		ft_putstr(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		write(1, &line[i], 1);
	return (i);
}

void	s_ctr_sl(int sig)
{
	char	*num;

	if (obj.pid)
	{
		kill(obj.pid, sig);
		ft_putstr("Quit: ");
		num = ft_itoa(sig);
		ft_putstr(num);
		ft_putstr("\n");
	}
	else
		ft_putstr("\b\b  \b\b");
}

void	s_ctr_c()
{
	errno = 1;
	ft_putstr("\b\b  \b\b");
	write(1, "\nminishell : ", 13);
}

int		main(int argc, char **argv, char **envp)
{
	int		i = 0;
	int		j;
	int		error;
	int		wh;
	char	*leaks;

	obj.standart_fd.fd_in = dup(0);
	obj.standart_fd.fd_out = dup(1);
	write(1, "minishell : ", 12);
	obj.pars.envp = envp;
	add_list_env(&obj.env_list, &obj.export_list ,obj.pars.envp);
	error = 0;
	signal(SIGINT, s_ctr_c);
	signal(3, s_ctr_sl);
	while (1)
	{
		j = 0;
		obj.pars.line = NULL;
		wh = get_next_line(&obj.pars.line, 0);
		if (wh < 0)
			exit(0);
		obj.pars.split_string = ft_split(obj.pars.line, ';');
		obj.flag.after_redir = 0;
		if (fn_check_before_redirect(&obj) != 0)
		{
			while (obj.pars.split_string[j] != NULL)
			{
				free(obj.pars.line);
				obj.pars.line = ft_strdup(obj.pars.split_string[j]);
				obj.flag.valid_com = 1;
				obj.flag.beg = 0;
				obj.flag.exist_pipe = 0;
				if ((fn_check_pipe(&obj)) == -1)
					break ;
				if (obj.flag.exist_pipe == 0)
					fn_pars_line(&obj);
				else
				{
					i = 0;
					obj.pars.line_for_pipe = NULL;
					if (!(obj.pars.line_for_pipe = ft_split(obj.pars.line, '|')))
						fn_error("not memory allocate\n");
					while (obj.pars.line_for_pipe[i] != NULL)
					{
						leaks = obj.pars.line_for_pipe[i];
						obj.pars.line_for_pipe[i] = ft_strtrim(obj.pars.line_for_pipe[i], " ");
						free(leaks);
						i++;
					}
					obj.flag.p_flag.count_pipe = i;
					if (!(obj.pars.command_for_pipe = malloc(sizeof(char *) * (i + 1))))
						fn_error("no memory allocate");
					obj.pars.command_for_pipe[i] = NULL;
					if (!(obj.pars.argument_for_pipe = malloc(sizeof(char *) * (i + 1))))
						fn_error("no memory allocate");
					obj.pars.argument_for_pipe[i] = NULL;
					i = 0;
					while (obj.pars.line_for_pipe[i] != NULL)
					{
						obj.flag.beg = 0;
						leaks = obj.pars.line;
						obj.pars.line = ft_strdup(obj.pars.line_for_pipe[i]);
						free(leaks);
						if (fn_pars_line(&obj) == 0)
						{
							error = 1;
							break ;
						}
						obj.pars.command_for_pipe[i] = ft_strdup(obj.pars.command);
						free(obj.pars.command);
						obj.pars.argument_for_pipe[i] = ft_strdup(obj.pars.argument);
						free(obj.pars.argument);
						i++;
					}
					if (error == 1)
						break ;
					if ((fn_process_for_pipes(&obj)) == 0)
						break ;
					free_double_array(obj.pars.command_for_pipe);
					free_double_array(obj.pars.line_for_pipe);
					free_double_array(obj.pars.argument_for_pipe);
				}
				j++;
			}
			free_double_array(obj.pars.split_string);
		}
		if (obj.redirect.fd != 1)
		{
			close(obj.redirect.fd);
			obj.redirect.fd = 1;
		}
		if (obj.redirect.fd_back_redirect != 0)
		{
			close(obj.redirect.fd_back_redirect);
			obj.redirect.fd_back_redirect = 0;
		}
		write(1, "minishell : ", 12);
		free(obj.pars.line);
	}
	write(1, "\n", 1);
	return (0);
}
