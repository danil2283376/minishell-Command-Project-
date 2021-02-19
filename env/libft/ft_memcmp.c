/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:38:07 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:38:32 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	unsigned int	start;

	start = 0;
	ptr1 = (unsigned char *)arr1;
	ptr2 = (unsigned char *)arr2;
	while (start < n)
	{
		if (ptr1[start] > ptr2[start])
			return (ptr1[start] - ptr2[start]);
		else if (ptr1[start] < ptr2[start])
			return (ptr1[start] - ptr2[start]);
		start++;
	}
	return (0);
}
