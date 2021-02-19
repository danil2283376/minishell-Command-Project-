/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:15:56 by scolen            #+#    #+#             */
/*   Updated: 2020/11/13 16:44:07 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			start;

	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	start = 0;
	if (n > 0)
	{
		while (start < n)
		{
			dst[start] = src[start];
			if (src[start] == (unsigned char)c)
				return (&dst[start + 1]);
			start++;
		}
	}
	return (NULL);
}
