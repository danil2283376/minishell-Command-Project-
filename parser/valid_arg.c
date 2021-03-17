/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:04:49 by melisha           #+#    #+#             */
/*   Updated: 2021/03/16 14:33:40 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_valid_arg(t_obj *obj)
{
	if (obj->flag.c_flag.exp == 1)
		fn_valid_exp(obj);
	if (obj->flag.c_flag.un == 1)
		fn_valid_un(obj);
	if (obj->flag.c_flag.en == 1)
		fn_valid_en(obj);
	if (obj->flag.c_flag.exi == 1)
		fn_valid_exi(obj);
	if (obj->flag.c_flag.cd == 1)
		fn_valid_cd(obj);
	if (obj->flag.c_flag.ec == 1)
		fn_valid_ec(obj);
	if (obj->flag.c_flag.pw == 1)
		fn_valid_pw(obj);
}