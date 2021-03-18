/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_error_processing_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:16:59 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 15:19:30 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void		fn_error_valid_redir_zero(t_obj *obj)
{
	obj->flag.beg = ft_strlen(obj->pars.line);
	obj->redirect.count_red -= 2;
	if (obj->redirect.count_red == 0)
		write(2, "minishell : syntax err\
or near unexpected token `>'\n", 51);
	else
		write(2, "minishell : syntax err\
or near unexpected token `>>'\n", 52);
}

void		fn_error_valid_redir_minus(t_obj *obj)
{
	write(2, "minishell : syntax er\
ror near unexpected token `newline'\n", 57);
	obj->flag.beg = ft_strlen(obj->pars.line);
}

void		fn_error_valid_back_redir_minus(t_obj *obj)
{
	write(2, "minishell : ", 12);
	write(2, obj->pars.redirect, ft_strlen(obj->pars.redirect));
	write(2, ": ", 2);
	perror(NULL);
	obj->flag.beg = ft_strlen(obj->pars.line);
}

void		fn_error_valid_back_redir_zero(t_obj *obj)
{
	obj->redirect.count_red -= 3;
	if (obj->redirect.count_red == -1)
		write(2, "minishell : syntax er\
ror near unexpected token `<'\n", 51);
	else if (obj->redirect.count_red == 0)
		write(2, "minishell : syntax er\
ror near unexpected token `<<'\n", 52);
	else
		write(2, "minishell : syntax er\
ror near unexpected token `<<<'\n", 53);
}

void		fn_error_mult_com(t_obj *obj)
{
	write(1, "minishell : multiple com\
mands are prohibited by subject\n", 56);
	obj->flag.beg = ft_strlen(obj->pars.line);
}
