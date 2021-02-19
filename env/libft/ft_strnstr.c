/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:13:04 by scolen            #+#    #+#             */
/*   Updated: 2020/11/07 20:45:45 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		f_s(char *start_str, const char *little, size_t start_s1)
{
	size_t start;
	size_t len_little;
	size_t len_s1;

	start = 0;
	len_little = ft_strlen(little);
	len_s1 = ft_strlen(start_str);
	while (start < len_little && start <= start_s1 && start < len_s1)
	{
		if (start_str[start] == little[start])
			start++;
		else
			break ;
	}
	if (start == len_little)
		return (1);
	else
		return (0);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	start;
	size_t	equal_string;
	char	*ptr;
	size_t	len_little;

	start = 0;
	len_little = ft_strlen(little);
	equal_string = 0;
	ptr = (char *)big;
	if (len_little == 0)
		return (&ptr[0]);
	while (start < len)
	{
		equal_string = f_s(&ptr[start], little, len - start);
		if (equal_string == 1)
			return (&ptr[start]);
		start++;
	}
	if (f_s(&ptr[0], little, len))
		return (&ptr[0]);
	return (NULL);
}
