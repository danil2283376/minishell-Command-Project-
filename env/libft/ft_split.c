/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:45:55 by scolen            #+#    #+#             */
/*   Updated: 2020/11/13 16:37:51 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	quantity_words(char const *s, char c)
{
	unsigned int start;
	unsigned int quantity_word;

	start = 0;
	quantity_word = 0;
	while (s[start] && s[start + 1])
	{
		if (s[start] == c && s[start + 1] != c)
			quantity_word++;
		start++;
	}
	return (quantity_word);
}

static int	length_word(char const *s, char c)
{
	unsigned int start;

	start = 0;
	while (s[start] != c && s[start] != '\0')
		start++;
	return (start);
}

static char	**free_array(char **ptr)
{
	free(ptr);
	return (NULL);
}

static char	*excretion_memory(char *ptr, char const *s, long len_w)
{
	unsigned int start;
	unsigned int len_word;

	len_word = 0;
	start = 0;
	ptr = (char *)malloc((len_w + 1) * sizeof(char));
	if (ptr == NULL)
		return (*free_array(&ptr));
	while (start < len_w)
	{
		ptr[start] = s[start];
		start++;
	}
	ptr[start] = '\0';
	return (ptr);
}

char		**ft_split(char const *s, char c)
{
	char **ptr;
	long arr[3];

	if (s == NULL)
		return (NULL);
	if (!(ptr = (char **)malloc((quantity_words(s, c) + 2) * sizeof(char *))))
		return (free_array(ptr));
	arr[0] = 1;
	arr[1] = 0;
	arr[2] = 0;
	while (s[arr[1]] != '\0')
	{
		if (s[arr[1]] != c)
		{
			arr[0] = length_word(&s[arr[1]], c);
			ptr[arr[2]] = excretion_memory(ptr[arr[2]], &s[arr[1]], arr[0]);
			arr[2]++;
		}
		arr[1] = arr[1] + arr[0];
		arr[0] = 1;
	}
	ptr[arr[2]] = NULL;
	return (ptr);
}
