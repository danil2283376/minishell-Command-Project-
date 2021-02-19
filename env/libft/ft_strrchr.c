/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:58:27 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:39:17 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	size_t	length;
	char	*ptr;

	length = ft_strlen(str);
	ptr = (char *)str;
	while (length > 0)
	{
		if (ptr[length] == (unsigned char)ch)
			return (&ptr[length]);
		length--;
	}
	if (ptr[length] == (unsigned char)ch)
		return (&ptr[length]);
	else
		return (NULL);
}
