/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:15:56 by scolen            #+#    #+#             */
/*   Updated: 2020/11/10 10:19:21 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	char			*ptr;
	unsigned int	start_ptr;
	unsigned int	start_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	start_ptr = 0;
	start_s = 0;
	ptr = (char *)malloc((len_s1 + len_s2) + 1);
	if (ptr == NULL)
		return (NULL);
	while (start_s < len_s1)
		ptr[start_ptr++] = s1[start_s++];
	start_s = 0;
	while (start_s < len_s2)
		ptr[start_ptr++] = s2[start_s++];
	ptr[start_ptr] = '\0';
	return (ptr);
}
