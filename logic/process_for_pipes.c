/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_for_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:59:03 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 13:22:19 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"
/*
*   obj->pars       // местоположение
*   char            **line_for_pipe; // строки комманд и аргументов
*   char            **command_for_pipe; // комманды в двумерном массиве
*   char            **argument_for_pipe; // аргументы комманд в двумерном массиве
*/

char    *ft_my_strjoin(char const *s1, char const *s2)
{
	unsigned int    len_s1;
	unsigned int    len_s2;
	char            *ptr;
	unsigned int    start_ptr;
	unsigned int    start_s;
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

void    free_double_array(char **array)
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

void    search_command_varible_path(t_obj *obj, int o)
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
    obj->flag.exist_pipe = 0;
    obj->pars.line_for_pipe[o] = fn_circumcision(obj->pars.line_for_pipe[o], obj);
    obj->flag.exist_pipe = 1;
    argv = ft_split(obj->pars.line_for_pipe[o], ' ');
    obj->pars.command = ft_strdup(obj->pars.command_for_pipe[o]);
    obj->flag.valid_com = fn_valid_command(obj);
    if (obj->flag.valid_com == 0 && obj->flag.after_redir != 1)
    {
        obj->pars.line = ft_strdup(obj->pars.command_for_pipe[o]);
        obj->flag.beg = 0;
        fn_pars_line(obj);
        if (obj->redirect.fd_back_redirect != 0)
            dup2(obj->redirect.fd_back_redirect, 0);
        varible_path = fn_search_enviroment(obj, "PATH");
        if (varible_path != NULL)
        {
            while (varible_path[i] != '\0')
            {
                while (varible_path[j] != ':' && varible_path[j])
                    j++;
                new_path = malloc(j + 1);
                while (varible_path[i] != ':' && varible_path[i] != '\0')
                {
                    new_path[k] = varible_path[i++];
                    k++;
                }
                new_path[k] = '\0';
                leaks = new_path;
                new_path = ft_my_strjoin(new_path, "/");
                leaks = new_path;
                new_path = ft_my_strjoin(new_path, obj->pars.command_for_pipe[o]);
                error = execve(new_path, &argv[0], obj->pars.envp);
                if (varible_path[i] == ':')
                {
                    i++;
                    count++;
                }
                j = 0;
                k = 0;
            }
        }
        else
            error = -1;
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
        obj->redirect.fd_back_redirect = 0;
    }
    else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1)
    {
        obj->pars.argument = ft_strdup(obj->pars.argument_for_pipe[o]);
        fn_valid_arg(obj);
    }
    free_double_array(argv);
}

int     fn_check_red(t_obj *obj, int i)
{
    int     j;
    j = 0;
    if (i != 0)
    {
        i--;
        while (obj->pars.line_for_pipe[i][j])
        {
            if (obj->pars.line_for_pipe[i][j] == '>')
                return (-1);
            j++;
        }
    }
    return (1);
}

int     threatment_pipe(t_obj *obj)
{
    int fd[2];
    int i;
    int error;
    int last_command;
    char *leaks;
    i = 0;
    error = 0;
    last_command = 0;
    while (i < obj->flag.p_flag.count_pipe)
    {
        if (i < obj->flag.p_flag.count_pipe - 1)
            pipe(fd);
        if ((obj->pid = fork()) == 0)
        {
            obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
            fn_pars_line(obj);
            if (obj->redirect.fd != 1)
            {
                dup2(obj->redirect.fd, 1);
                close(fd[0]);
                close(fd[1]);
            }
            else
            {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
                if (obj->flag.after_redir != 1)
                    search_command_varible_path(obj, i);
            }
            exit(0);
        }
        else
        {
            obj->flag.beg = 0;
            leaks = obj->pars.line;
            obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
            free(leaks);
            fn_pars_line(obj);
			if (obj->pars.argument)
				free(obj->pars.argument);
			if (obj->pars.command)
				free(obj->pars.command);
			obj->flag.after_redir = 0;
            if (obj->redirect.fd != 1)
            {
                obj->flag.beg = 0;
                obj->flag.after_redir = 1;
                leaks = obj->pars.line;
                obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
                free(leaks);
                obj->flag.exist_pipe = 0;
                fn_pars_line(obj);
				leaks = obj->pars.line;
                obj->pars.line = fn_circumcision(obj->pars.line, obj);
				free(leaks);
                leaks = obj->pars.line_for_pipe[i];
                obj->pars.line_for_pipe[i] = ft_strdup(obj->pars.line);
                free(leaks);
                obj->flag.exist_pipe = 1;
                dup2(obj->redirect.fd, 0);
                close(fd[0]);
                close(fd[1]);
                int		status;
				waitpid(obj->pid, &status, 0);
				errno = WEXITSTATUS(status);
            }
            else
            {
                dup2(fd[0], 0);
                close(fd[0]);
                close(fd[1]);
                int		status;
				waitpid(obj->pid, &status, 0);
				errno = WEXITSTATUS(status);
            }
        }
        obj->pid = 0;
        i++;
    }
    dup2(obj->standart_fd.fd_in, 0);
    dup2(obj->standart_fd.fd_out, 1);
    obj->redirect.fd_back_redirect = 0;
    obj->redirect.fd = 1;
    return (1);
}

int     fn_process_for_pipes(t_obj *obj)
{
	int     i;
	char    *leaks;
	char    *path;
	int     j;
	int     k;
	int     len;
	i = 0;
	if (obj->flag.exist_pipe == 1)
		threatment_pipe(obj);
	else
	{
		obj->flag.valid_com = fn_valid_command(obj);
		if (obj->redirect.fd != 1)
			dup2(obj->redirect.fd, 1);
		if (obj->flag.valid_com == 0)
		{
			if (obj->redirect.fd_back_redirect != 0)
				dup2(obj->redirect.fd_back_redirect, 0);
			int error = 0;
			if ((obj->pid = fork()) == 0)
			{
				char **argv;
				j = 0;
				path = fn_search_enviroment(obj, "PATH");
				if (path != NULL)
				{
					len = ft_strlen(path);
					if (obj->redirect.fd_back_redirect != 0)
						obj->flag.exist_pipe = 0;
					obj->pars.line = fn_circumcision(obj->pars.line, obj);
					obj->flag.exist_pipe = 1;
					argv = ft_split(obj->pars.line, ' ');
					while (path[j])
					{
						k = j;
						if (j == -1)
							j++;
						while (path[j] != ':' && path[j])
							j++;
						if (path[j] == ':')
						{
							path[j] = '\0';
							j++;
						}
						char *new_str;
						new_str = ft_strjoin(&path[k], "/");
						new_str = ft_strjoin(new_str, obj->pars.command);
						error = execve(new_str, &argv[0], obj->pars.envp);
						if (error != -1)
							break ;
					}
					if (error == -1)
					{
						error = execve(obj->pars.command, &argv[0], obj->pars.envp);
						if (error == -1)
							fn_command_not_found(obj);
					}
				}
				else
				{
					argv = ft_split(obj->pars.line, ' ');
					error = execve(obj->pars.command, &argv[0], obj->pars.envp);
					if (error == -1)
						fn_command_not_found(obj);
				}
				exit(errno);
			}
			else
			{
				int		status;
				waitpid(obj->pid, &status, 0);
				errno = WEXITSTATUS(status);
			}
			if (error == -1)
			{
				fn_command_not_found(obj);
				return (0);
			}
			if (obj->redirect.fd_back_redirect != 0)
				dup2(obj->standart_fd.fd_out, 0);
			obj->redirect.fd_back_redirect = 0;
			obj->flag.valid_com = 1;
			obj->pid = 0;
		}
		else if (obj->flag.valid_com != 0 && obj->flag.valid_redir == 1) //Выполняю НАШИ функции (echo)
			fn_valid_arg(obj);
		free(obj->pars.command);
		free(obj->pars.argument);
	}
	dup2(obj->standart_fd.fd_in, 0);
	dup2(obj->standart_fd.fd_out, 1);
	obj->redirect.fd = 1;
	return (1);
}