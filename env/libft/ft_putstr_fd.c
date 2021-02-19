/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:19:07 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 20:25:25 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int start;

	start = 0;
	if (s == NULL)
		return ;
	while (s[start] != '\0')
	{
		ft_putchar_fd(s[start], fd);
		start++;
	}
}
