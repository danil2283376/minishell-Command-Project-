/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:58:37 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 21:37:11 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H
# include "../../libminishell.h"

void	fn_valid_exp(t_obj *obj);
void	fn_valid_un(t_obj *obj);
void	fn_valid_en(t_obj *obj);
void	fn_valid_exi(t_obj *obj);
void	fn_valid_cd(t_obj *obj);
void	fn_valid_pw(t_obj *obj);
void	fn_valid_ec(t_obj *obj);
int		not_exist_equal(t_obj *obj, t_export *export, int start);
#endif
