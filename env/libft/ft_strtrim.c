/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:11:28 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 19:39:23 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_char(char c, char const *set)
{
	size_t start;

	start = 0;
	while (set[start] != '\0')
	{
		if (c == set[start])
			return (1);
		start++;
	}
	return (0);
}

static int		start_index_f(char const *s1, char const *set)
{
	int start_index;
	int len_s1;

	len_s1 = ft_strlen(s1);
	start_index = 0;
	while (check_char(*s1++, set) && start_index < len_s1)
		start_index++;
	return (start_index);
}

static int		end_index_f(char const *s1, char const *set)
{
	unsigned int index_end;
	unsigned int start_index;

	index_end = (ft_strlen(s1) - 1);
	start_index = 0;
	while (check_char(s1[index_end], set) && index_end > 0)
		index_end--;
	return (index_end);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start_index;
	unsigned int	end_index;
	unsigned int	start_ptr;
	char			*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return ((char *)s1);
	start_index = start_index_f(s1, set);
	end_index = end_index_f(s1, set);
	ptr = malloc((end_index - start_index) + 2);
	if (ptr == NULL)
		return (NULL);
	start_ptr = 0;
	while (start_index <= end_index)
	{
		ptr[start_ptr] = s1[start_index];
		start_ptr++;
		start_index++;
	}
	ptr[start_ptr] = '\0';
	return (ptr);
}
