/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:35:35 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:38:26 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned int	start;

	ptr = (unsigned char*)arr;
	start = 0;
	while (start < n)
	{
		if (ptr[start] == (unsigned char)c)
		{
			return (&ptr[start]);
		}
		start++;
	}
	return (NULL);
}
