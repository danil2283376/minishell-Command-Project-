/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:06:17 by melisha           #+#    #+#             */
/*   Updated: 2021/02/14 13:46:36 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

static int	ft_beginner(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
		{
			j++;
		}
		if (set[j] != s1[i] && set[j] == '\0')
			break ;
		i++;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = ft_strlen(s1);
	while (i >= 0)
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
		{
			j++;
		}
		if (set[j] != s1[i] && !set[j])
			break ;
		i--;
	}
	return (i + 1);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		i;
	int		begin;
	int		end;

	if (!s1)
		return (NULL);
	begin = ft_beginner(s1, set);
	end = ft_end(s1, set);
	if (begin >= end)
	{
		if (!(s = (char *)ft_calloc(1, sizeof(char))))
			return (NULL);
	}
	else
	{
		if (!(s = (char *)malloc((end - begin + 1) * sizeof(char))))
			return (NULL);
		i = 0;
		while (s1[begin] && begin < end)
			s[i++] = s1[begin++];
		s[i] = '\0';
	}
	return (s);
}
