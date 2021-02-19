/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:54:11 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:38:42 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			start;

	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	start = 0;
	if (dst > src && n != 0 && dst != NULL && src != NULL)
	{
		while (--n > 0)
			dst[n] = src[n];
		dst[n] = src[n];
	}
	else
	{
		while (start < n && (dst != NULL || src != NULL))
		{
			dst[start] = src[start];
			start++;
		}
	}
	return ((void *)dst);
}
