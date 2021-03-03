/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:09:25 by melisha           #+#    #+#             */
/*   Updated: 2021/03/03 11:41:46 by scolen           ###   ########.fr       */
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
	t_com_flags		c_flag;
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
	char			**line_for_pipe;
	char			*redirect;
	char			*arg_for_back_redirect;
	char			*command;
	char			*argument;
	char			**envp;
}					t_pars;
typedef struct		s_obj
{
	t_redirect		redirect;
	t_flags			flag;
	t_pars			pars;
	t_list		env_list;
	t_list		export_list;
}					t_obj;
#endif
