/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_for_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:59:03 by melisha           #+#    #+#             */
/*   Updated: 2021/03/13 15:16:28 by melisha          ###   ########.fr       */
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

void	delete_space(t_obj *obj) 
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

char	*ft_my_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	char			*ptr;
	unsigned int	start_ptr;
	unsigned int	start_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	start_ptr = 0;
	start_s = 0;
	ptr = (char *)malloc((len_s1 + len_s2) + 1);
	if (ptr == NULL)
		return (NULL);
	while (start_s < len_s1)
		ptr[start_ptr++] = s1[start_s++];
	start_s = 0;
	while (start_s < len_s2)
		ptr[start_ptr++] = s2[start_s++];
	ptr[start_ptr] = '\0';
	return (ptr);
}

void	free_double_array(char **array) 
{
	int i;

	i = 0;
	while (array[i]) 
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	search_command_varible_path(t_obj *obj, int o)
{
	int i;
	int j;
	int k;
	char *varible_path;
	char *new_path;
	int error = -1;
	int count = 0;
	char *leaks;

	i = 0;
	j = 0;
	k = 0;
	char **argv;
	argv = ft_split(obj->pars.line_for_pipe[o], ' ');
	obj->pars.command = ft_strdup(obj->pars.command_for_pipe[o]);
	obj->flag.valid_com = fn_valid_command(obj);
	if (obj->flag.valid_com == 0)
	{
		varible_path = fn_search_enviroment(obj, "PATH");
		while (varible_path[i] != '\0')
		{
			while (varible_path[j] != ':')
				j++;
			new_path = malloc(j + 1);
			while (varible_path[i] != ':' && varible_path[i] != '\0')
			{
				new_path[k] = varible_path[i++];
				k++;
			}
			new_path[k] = '\0';
			new_path = ft_my_strjoin(new_path, "/");
			new_path = ft_my_strjoin(new_path, obj->pars.command_for_pipe[o]);
			// argv = ft_split(obj->pars.line_for_pipe[o], ' ');
			// obj->pars.line = ft_strdup(obj->pars.line_for_pipe[o]);
			error = execve(new_path, &argv[0], obj->pars.envp);
			if (varible_path[i] == ':')
			{
				i++;
				count++;
			}
			j = 0;
			k = 0;
		}
		if (error == -1)
		{
			error = execve(obj->pars.command_for_pipe[o], &argv[0], obj->pars.envp);
			if (error == -1)
			{
				errno = 127;
				write(2, "minishell : ", 12);
				write(2, argv[0], ft_strlen(argv[0]));
				write(2, " : command not found\n", 21);
				exit(errno);
			}
		} 
		free_double_array(argv);
	}
	else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1) //Выполняю НАШИ функции (echo)
	{
		obj->pars.argument = ft_strdup(obj->pars.argument_for_pipe[o]);
		fn_valid_arg(obj);
	}
}

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
	while (i < obj->flag.p_flag.count_pipe)
	{
		if (i < obj->flag.p_flag.count_pipe - 1)
			pipe(fd);
		if ((pid = fork()) == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			search_command_varible_path(obj, i);
			exit(1);
		}
		else
		{
			if (obj->pars.argument_for_pipe[i])
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			wait(&pid);
		}
		i++;
	}
	dup2(obj->standart_fd.fd_in, 0);
	return (1);
}

int		threatment_command(t_obj *obj)
{
	return (1);
}

int	threatment_solo_command(t_obj *obj, int o) 
{
	int i;
	int j;
	int k;
	char *varible_path;
	char *new_path;
	int error;
	char **argv;

	i = 0;
	error = 0;
	varible_path = fn_search_enviroment(obj, "PATH");
	printf("SOSAT!\n");
	write (2, obj->pars.line_for_pipe[o], ft_strlen(obj->pars.line_for_pipe[o]));
	argv = ft_split(obj->pars.line_for_pipe[o], ' ');
	write(1, "1", 1);
	printf("%s\n", varible_path);
	while (varible_path[i] != '\0')
	{
		while (varible_path[j] != ':')
			j++;
		new_path = malloc(j + 1);
		while (varible_path[i] != ':' && varible_path[i] != '\0')
		{
			new_path[k] = varible_path[i++];
			k++;
		}
		new_path[k] = '\0';
		new_path = ft_my_strjoin(new_path, "/");
		new_path = ft_my_strjoin(new_path, obj->pars.command_for_pipe[o]);
		// argv = ft_split(obj->pars.line_for_pipe[o], ' ');
		// obj->pars.line = ft_strdup(obj->pars.line_for_pipe[o]);
		printf("%s\n", new_path);
		error = execve(new_path, &argv[0], obj->pars.envp);
		if (varible_path[i] == ':')
			i++;
		j = 0;
		k = 0;
		free(new_path);
	}
	return (error);
}

int		fn_process_for_pipes(t_obj *obj)
{
	int i;
	char *leaks;
	int		we_command;

	i = 0;
	we_command = 0;
    if (obj->flag.exist_pipe == 1)
    {
		threatment_pipe(obj);
    }
    else
    {
		obj->flag.valid_com = fn_valid_command(obj);
		if (obj->flag.valid_com == 0 && we_command == 0)
		{
			//ВСТАВЛЯЕШЬ EXECVE
			int error = 0;
			pid_t pid;
			// ЕСЛИ EXSECVE ВЕРНЕТ (-1), ТО РАСКОМЕНТИРУЙ НИЖЕ 2 СТРОКИ
			if ((pid = fork()) == 0)
			{
				char *new_str = "/bin/";
				new_str = ft_strjoin(new_str, obj->pars.command);
				char **argv;
				argv = ft_split(obj->pars.line, ' ');
				error = execve(new_str, &argv[0], obj->pars.envp);
				if (error == -1)
					fn_command_not_found(obj);
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