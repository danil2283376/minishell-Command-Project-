/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:47:04 by melisha           #+#    #+#             */
/*   Updated: 2021/02/14 17:47:13 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;
	int		sum;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	sum = (ft_strlen(s1) + ft_strlen(s2));
	if (!(s = (char *)malloc((sum + 1) * sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s[i] = s2[j];
		j++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
