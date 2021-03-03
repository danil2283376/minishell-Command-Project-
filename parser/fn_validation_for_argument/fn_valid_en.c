/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_valid_en.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:02:17 by melisha           #+#    #+#             */
/*   Updated: 2021/02/25 17:28:32 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	fn_valid_en(t_obj *obj)
{
	if (obj->pars.argument[fn_space(obj->pars.argument, 0)] != '\0')
		fn_too_many_arguments(obj);
	else
		output_list(&obj->env_list);
}