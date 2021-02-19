/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:54:19 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:39:06 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t start;
	size_t src_len;

	if (dst == NULL || src == NULL)
		return (sizeof(0));
	start = 0;
	src_len = ft_strlen(src);
	if (size != 0)
		size = size - 1;
	while ((start < size) && src[start] != '\0')
	{
		dst[start] = src[start];
		start++;
	}
	if (size != 0)
		dst[start] = '\0';
	return (src_len);
}
