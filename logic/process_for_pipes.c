/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_for_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:59:03 by melisha           #+#    #+#             */
/*   Updated: 2021/03/10 16:13:41 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_ctrl_sl(int key)
{
	write(1, "Quit: 3\n", 9);
	return ;
}

/* 
*	obj->pars 		// местоположение
*	char			**line_for_pipe; // строки комманд и аргументов
*	char			**command_for_pipe; // комманды в двумерном массиве
*	char			**argument_for_pipe; // аргументы комманд в двумерном массиве
*/

char 	*delete_space(t_obj *obj) 
{
	int i;

	i = 0;
	while (obj->pars.line_for_pipe[i] != NULL)
	{
		char *leak = obj->pars.line_for_pipe[i];
		obj->pars.line_for_pipe[i] = ft_strtrim(obj->pars.line_for_pipe[i], " ");
		free(leak);
		i++;
	}
}

// void	search_command_in_varible_path(t_obj *obj) 
// {
// 	int i;

// 	i = 0;
// 	char *command;
// 	while (obj->) 
// 	{

// 	}
// }

int		threatment_pipe(t_obj *obj)
{
	pid_t pid;
	int fd[2];
	int i;
	int error;
	int last_command;

	i = 0;
	error = 0;
	last_command = 0;
	delete_space(obj);
	printf("\n\nWRITE!!!\n\n");
	while (i < obj->flag.p_flag.count_pipe) 
	{
		if (i < obj->flag.p_flag.count_pipe - 1)
			pipe(fd);
		if ((pid = fork()) == 0) // ребенок
		{
			dup2(fd[1], 1); // меняю fd на вывод информации комманды
			close(fd[0]);
			close(fd[1]);
			char *new_str = "/bin/";
			new_str = ft_strjoin(new_str, obj->pars.command_for_pipe[i]);
			char **argv;
			argv = ft_split(obj->pars.line_for_pipe[i], ' ');
			error = execve(new_str, &argv[0]/*&obj->pars.line_for_pipe[i]*/, obj->pars.envp);
			exit(1);
		}
		else // родитель
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			wait(&pid);
		}
		i++;
	}
	dup2(obj->standart_fd.fd_in, 0);
	// dup2(obj->standart_fd.fd_in, 1);
	printf("i = %d\n", obj->flag.p_flag.count_pipe - 1);
	return (1);
}

// void	threatment_pipe(t_obj *obj, int i)
// {
// 	// int fd[2];
// 	pid_t pid;
// 	int error;

// 	pipe(obj->standart_fd.fd_pipe);
// 	pid = fork();
// 	if (pid == 0) 
// 	{
// 		dup2(obj->standart_fd.fd_pipe[1], STDOUT_FILENO);
// 		close(obj->standart_fd.fd_pipe[0]);
// 		close(obj->standart_fd.fd_pipe[1]);
// 		char **argv;
// 		argv = ft_split(obj->pars.line_for_pipe[i], ' ');

// 		char *new_str = "/bin/";
// 		new_str = ft_strjoin(new_str, obj->pars.command_for_pipe[i]);
// 		error = execve(new_str, &argv[0], obj->pars.envp);
// 		close(1);
// 	}
// 	else 
// 	{
// 		dup2(obj->standart_fd.fd_pipe[0], STDIN_FILENO);
// 		close(obj->standart_fd.fd_pipe[0]);
// 		close(obj->standart_fd.fd_pipe[0]);
// 		waitpid(pid, NULL, 0);
// 		dup
// 	}

	
// 	// pid_t pid;
// 	// int error;

// 	// pipe(obj->standart_fd.fd_pipe); // создал пайп
// 	// if ((pid = fork()) == 0) // ребенок
// 	// {
// 	// 	dup2(1, obj->standart_fd.fd_pipe[1]);
// 	// 	char **argv;
// 	// 	argv = ft_split(obj->pars.line_for_pipe[i], ' ');

// 	// 	char *new_str = "/bin/";
// 	// 	new_str = ft_strjoin(new_str, obj->pars.command_for_pipe[i]);
// 	// 	error = execve(new_str, &argv[0], obj->pars.envp);
// 	// 	close(obj->standart_fd.fd_pipe[0]);
// 	// 	close(obj->standart_fd.fd_pipe[1]);
// 	// 	exit(1);
// 	// }
// 	// else // родитель
// 	// {
// 	// 	dup2(0, obj->standart_fd.fd_pipe[0]); // подменял считывание
// 	// 	close(obj->standart_fd.fd_pipe[0]);  // закрыл fd, который уже заменил
// 	// 	close(obj->standart_fd.fd_pipe[1]); // закрыл fd, который уже заменил
// 	// 	wait(&pid);
// 	// 	dup2(0, obj->standart_fd.fd_in);
// 	// 	dup2(1, obj->standart_fd.fd_out);
// 	// }
// }

int		threatment_command(t_obj *obj)
{
	return (1);
}

int		fn_process_for_pipes(t_obj *obj)
{
	int i;

	i = 0;
	obj->flag.valid_com = fn_valid_command(obj); //VALIDATION_COMMAND
    if (obj->flag.exist_pipe == 1)
    {
		//обрабатываю пайпы
		// while (i < obj->flag.p_flag.count_pipe)
		// {
		// 	threatment_pipe(obj, i);
		// 	i++;
		// }
		threatment_pipe(obj);
    }
    else
    {
        //обрабатываю комманду
		if (obj->flag.valid_com == 0)
		{
			//ВСТАВЛЯЕШЬ EXECVE
			int error = 0;
			pid_t pid;
			// ЕСЛИ EXSECVE ВЕРНЕТ (-1), ТО РАСКОМЕНТИРУЙ НИЖЕ 2 СТРОКИ
			if ((pid = fork()) == 0)
			{
				// printf("HELL\n");
				// ХЗ ГДЕ ЛЕЖИТ 1 КОММАНДА
				char *new_str = "/bin/";
				new_str = ft_strjoin(new_str, obj->pars.command);
				char **argv;
				argv = ft_split(obj->pars.line, ' ');
				error = execve(new_str, &argv[0], obj->pars.envp);
				if (error == -1)
				{
					fn_command_not_found(obj);
				}
				exit(1);
			}
			else
				wait(&pid);
			if (error == -1)
			{
				fn_command_not_found(obj);
				return (0);
			}
		}
		else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1) //Выполняю НАШИ функции (echo)
			fn_valid_arg(obj);
		threatment_command(obj);
		
    }
	return (1);
}

// void threatment_pipe(t_obj *obj)
// {
// 	pid_t pid;
// 	int		i;
// 	int		chaeck_err;
// 	int		fd[obj->flag.p_flag.count_pipe][2];

// 	chaeck_err = 0;
// 	obj->flag.beg_for_pipe = 0;
// 	i = obj->flag.beg_for_pipe;
// 	while (i < obj->flag.p_flag.count_pipe)
// 	{
// 		pipe(fd[i]);
// 		if ((pid = fork()) == 0)
// 		{
// 			if (i != 0)
// 				dup2(fd[i - 1][0], 0);
// 			if (i + 1 != obj->flag.p_flag.count_pipe)
// 				dup2(fd[i][1], 1);
// 			// if (i + 1 == obj->flag.p_flag.count_pipe)
// 			// 	fd[i][1] = dup(fd[i - 1][1]);
// 			obj->flag.beg_for_pipe = i;
// 			obj->flag.beg = 0;
// 			obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
// 			fn_pars_line(obj);
// 			i = obj->flag.beg_for_pipe;
// 			if (obj->pars.line_for_pipe[i] == NULL)
// 				chaeck_err = 1;
// 			exit(0);
// 		}
// 		else
// 		{
// 			// dup2(fd[i][0], 0);
// 			if (i == 0)
// 				close(fd[i][0]);
// 			wait(&pid);
// 		}
// 		if (chaeck_err == 1)
// 			break ;
// 		if (obj->pars.line_for_pipe[i] != NULL)
// 			i++;
// 	}
// }

// int		fn_check_error_pipe(t_obj *obj)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	while (obj->pars.line[i])
// 	{
// 		if (obj->pars.line[i] == '>')
// 		{
// 			i++;
// 			if (obj->pars.line[fn_space(obj->pars.line, i)] == '|')
// 			{
// 				write(1, "minishell: syntax error near unexpected token '|'\n", 50);
// 				return (-1);
// 			}
// 		}
// 		if (obj->pars.line[i] == '|')
// 		{
// 			count = 1;
// 			while (obj->pars.line[++i] == '|')
// 				count++;
// 			if (count > 1)
// 			{
// 				write(1, "minishell: syntax error near unexpected token '||'\n", 51);
// 				return (-1);
// 			}
// 			else if (obj->pars.line[fn_space(obj->pars.line, i)] == '\0')
// 			{
// 				write(1, "minishell : multiple commands are prohibited by subject\n", 56);
// 				return (-1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	fn_process_for_pipes(t_obj *obj)
// {
// 	int i;

// 	i = 0;
// 	obj->flag.p_flag.count_pipe = 0;
// 	if ((fn_check_error_pipe(obj)) == -1)
// 		return ;
// 	if (!(obj->pars.line_for_pipe = ft_split(obj->pars.line, 124)))
// 		fn_error("not memory allocate\n");
// 	while (obj->pars.line_for_pipe[i] != NULL)
// 		i++;
// 	obj->flag.p_flag.count_pipe = i;
// 	threatment_pipe(obj);
// }