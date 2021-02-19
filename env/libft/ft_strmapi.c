/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:41:37 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 20:06:10 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len_s;
	unsigned int	start;
	char			*ptr;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	start = 0;
	ptr = malloc(len_s + 1);
	if (ptr == NULL)
		return (NULL);
	while (start < len_s)
	{
		ptr[start] = f(start, s[start]);
		start++;
	}
	ptr[start] = '\0';
	return (ptr);
}
