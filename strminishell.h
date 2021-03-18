/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:09:25 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 20:56:29 by melisha          ###   ########.fr       */
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
	int				after_redir;
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
	char			**line_for_pipe;
	char			**command_for_pipe;
	char			**argument_for_pipe;
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
	pid_t			pid;
	t_redirect		redirect;
	t_flags			flag;
	t_pars			pars;
	t_standart_out	standart_fd;
	t_list		env_list;
	t_list		export_list;
}					t_obj;
typedef	struct	s_mass
{
	int		i;
	int		len;
	char	*com;
}				t_mass;
typedef struct      s_varible_list
{
    t_list  *copy;
    t_list  *copy_before;
    t_list  *copy_after;
    t_list  *current;
    int     len_value;
    char    *name_varible;
    char    *value_varible;
}                   t_varible_list;
typedef struct      s_pipes
{
    char    *path;
    int     error;
    char    **argv;
    int     fd[2];
    int     len;
}                   t_pipes;
typedef	struct s_env_var
{
	int		i;
	int		j;
	char	ch;
	char	*line;
	char	*name;
	char	*value;
	char	*leaks;
	char	*num;
}				t_env_var;
typedef struct      s_cd
{
    int     i;
    int     len;
    int     start;
    char    *value;
    char    *home;
    char    *pwd;
    char    *save_arg;
    char    *leaks;
}                   t_cd;
typedef struct      s_echo
{
    int     i;
    int     len;
    int     start;
    char    *new_arg;
}                   t_echo;
typedef struct      s_export
{
    char    *name;
    char    *value;
    char    *arg;
    char    ch;
    int     j;
    int     k;
    int     f;
    char    *leaks;
    char    *val;
}                   t_export;
typedef struct      s_threatment_pipe
{
    int fd[2];
    int i;
    int error;
    int last_command;
    char *leaks;
}                   t_threatment_pipe;
typedef struct      s_process_for_pipes
{
    int     i;
    char    *leaks;
    char    *path;
    int     j;
    int     k;
    int     len;
    int     error;
    char    **argv;
}                   t_process_for_pipes;
typedef struct      s_command_varible_path
{
    int i;
    int j;
    int k;
    char *path;
    char *new_path;
    int error;
    int count;
    char **argv;
}                   t_command_varible_path;
#endif
