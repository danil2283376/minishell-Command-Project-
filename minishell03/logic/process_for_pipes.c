/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_for_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:59:03 by melisha           #+#    #+#             */
/*   Updated: 2021/03/05 11:22:31 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void threatment_pipe(t_obj *obj)
{
	pid_t pid;
	int		i;
	int		chaeck_err;
	// int		fd[2];
	// int len_arr = ft_strlen_double_arr(obj->pars.line_for_pipe);
	// int		fd[len_arr][2];

	// chaeck_err = 0;
	// obj->flag.beg_for_pipe = 0;
	// i = obj->flag.beg_for_pipe;
	// while (obj->pars.line_for_pipe[i] != NULL)
	// {
	// 	pipe(fd[i]);
	// 	if ((pid = fork()) == 0)
	// 	{
	// 		dup2(fd[i][1], 1);
	// 		close(fd[i][0]);
			obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
			fn_pars_line(obj);
	// 		i = obj->flag.beg_for_pipe;
	// 		if (obj->pars.line_for_pipe[i] == NULL)
	// 			chaeck_err = 1;
	// 		// execve(,);
	// 		exit(1);
	// 	}
	// 	else
	// 	{
	// 		dup2(fd[i][0], 0);
	// 		close(fd[i][1]);
	// 	}
	// 	i++;
	// }



	// while (obj->pars.line_for_pipe[i] != NULL)
	// {
	// 	if ((pid = fork()) == 0)
	// 	{
	// 		pipe(fd[i]);
	// 		// dup(fd[1]);
	// 		close(fd[i][0]);
	// 		dup2(fd[i][1], 0);
	// 		close(fd[i][1]);
	// 		obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
	// 		fn_pars_line(obj);
	// 		i = obj->flag.beg_for_pipe;
	// 		if (obj->pars.line_for_pipe[i] == NULL)
	// 			chaeck_err = 1;
	// 		// execve(,);
	// 		exit(1);
	// 	}
	// 	else
	// 		wait(&pid);
	// 	if (chaeck_err == 1)
	// 		break ;
	// 	i++;
	// }
}

void	fn_process_for_pipes(t_obj *obj)
{
	int i;

	i = 0;
	if (!(obj->pars.line_for_pipe = ft_split(obj->pars.line, 124)))
		fn_error("not memory allocate\n");
	threatment_pipe(obj);
}
