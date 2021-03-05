/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:34:27 by melisha           #+#    #+#             */
/*   Updated: 2021/02/22 16:34:39 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	*ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*sarr;

	sarr = (char *)s;
	i = 0;
	while (i < n)
	{
		sarr[i] = '\0';
		i++;
	}
	return (s);
}
