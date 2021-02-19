/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:30:13 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:39:02 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t start;
	size_t length_dst;
	size_t length_src;
	size_t length_length_dst;
	size_t i;

	start = 0;
	length_dst = ft_strlen(dst);
	length_src = ft_strlen(src);
	length_length_dst = length_dst;
	i = ft_strlen(dst);
	if (dst == NULL && src == NULL)
		return (0);
	if (ft_strlen(dst) > size || size == 0)
		return (ft_strlen(src) + size);
	while ((size - 1) > length_dst++ && src[start])
	{
		dst[i++] = src[start];
		start++;
	}
	dst[i] = '\0';
	return (length_length_dst + length_src);
}
