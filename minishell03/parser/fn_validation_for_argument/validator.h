/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:58:37 by melisha           #+#    #+#             */
/*   Updated: 2021/02/21 15:05:26 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libminishell.h"

#ifndef VALIDATOR_H
#define VALIDATOR_H
void	fn_valid_exp(t_obj *obj);
void	fn_valid_un(t_obj *obj);
void	fn_valid_en(t_obj *obj);
void	fn_valid_exi(t_obj *obj);
void	fn_valid_cd(t_obj *obj);
void	fn_valid_pw(t_obj *obj);
void	fn_valid_ec(t_obj *obj);
#endif