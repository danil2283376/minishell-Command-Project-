/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:09:25 by melisha           #+#    #+#             */
/*   Updated: 2021/03/10 16:58:44 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRMINISHELL_H
# define STRMINISHELL_H

typedef struct		s_list
{
	void			*key;
	void			*content;
	struct s_list	*next;
}					t_list;
typedef struct		s_com_flags
{
	int		exp;
	int		un;
	int		en;
	int		exi;
	int		cd;
	int		ec;
	int		fl_ec;
	int		pw;
	int		envir;
}					t_com_flags;
typedef struct		s_pipe_flag
{
	int				count_pipe;
}					t_pipe_flag;
typedef struct		s_flags
{
	int				beg;
	int				exist_pipe;
	char			quote;
	int				multiple_com;
	int				valid_com;
	int				valid_arg;
	int				valid_redir;
	int				valid_back_red;
	int				back_redirect;
	int				environment_variable;
	int				without_mistake;
	t_com_flags		c_flag;
	t_pipe_flag		p_flag;
}					t_flags;
typedef struct		s_redirect
{
	int				fd;
	int				fd_back_redirect;
	int				count_red;
}					t_redirect;
typedef struct		s_pars
{
	char			*line;
	char			**split_string;
	char			**line_for_pipe; // строки комманд и аргументов
	char			**command_for_pipe; // комманды в двумерном массиве
	char			**argument_for_pipe; // аргументы комманд в двумерном массиве
	char			*redirect;
	char			*arg_for_back_redirect;
	char			*command;
	char			*argument;
	char			**envp;
}					t_pars;
typedef struct		s_standart_out
{
	int	fd_in;
	int fd_out;
	int	fd_pipe[2];
}					t_standart_out;
typedef struct		s_obj
{
	t_redirect		redirect;
	t_flags			flag;
	t_pars			pars;
	t_standart_out	standart_fd;
	t_list		env_list;
	t_list		export_list;
}					t_obj;
#endif
