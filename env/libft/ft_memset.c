/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:58:11 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:38:46 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t			start;
	unsigned char	*ptr;

	start = 0;
	ptr = destination;
	if (n > 0)
	{
		while (start < n)
			ptr[start++] = (char)c;
		return (destination);
	}
	return (ptr);
}
