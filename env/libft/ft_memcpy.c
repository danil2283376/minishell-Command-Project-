/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:57:37 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:38:37 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	unsigned int	start;

	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	start = 0;
	if (destination == 0 && source == 0)
		return (0);
	while (start < n)
	{
		dst[start] = src[start];
		start++;
	}
	return (dst);
}
