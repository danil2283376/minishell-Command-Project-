/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:39:59 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:38:53 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	unsigned char	symbol;
	unsigned int	start;
	char			*ptr;

	start = 0;
	ptr = (char *)str;
	symbol = (unsigned char)ch;
	while (ptr[start] != '\0')
	{
		if (ptr[start] == symbol)
			return (&ptr[start]);
		start++;
	}
	if (ptr[start] == symbol)
		return (&ptr[start]);
	return (NULL);
}
