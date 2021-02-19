/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:57:19 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:38:56 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	unsigned int	start;
	unsigned int	length_str;
	char			*ptr;

	start = 0;
	length_str = ft_strlen(str);
	ptr = malloc((length_str + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (start < length_str)
	{
		ptr[start] = str[start];
		start++;
	}
	ptr[start] = '\0';
	return (ptr);
}
