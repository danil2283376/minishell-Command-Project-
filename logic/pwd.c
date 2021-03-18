/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:05:10 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 12:47:42 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	ft_pwd(void)
{
	char	*buf;

	if (!(buf = malloc(100000)))
		fn_error("no memory allocate");
	getcwd(buf, 100000);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
}
