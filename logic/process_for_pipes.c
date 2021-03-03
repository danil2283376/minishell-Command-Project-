/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_for_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:59:03 by melisha           #+#    #+#             */
/*   Updated: 2021/03/03 11:38:52 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	fn_process_for_pipes(t_obj *obj)
{
    int i;

    i = 0;
    if (!(obj->pars.line_for_pipe = ft_split(obj->pars.line, 124)))
		fn_error("not memory allocate\n");
	while (obj->pars.line_for_pipe[i])
    {
        obj->pars.line = ft_strdup(obj->pars.line_for_pipe[i]);
        fn_pars_line(obj);
		i++;
    }
}
