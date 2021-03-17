/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:27:17 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 11:27:33 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	if (!(s2 = (char *)malloc(((ft_strlen(s1) + 1) * sizeof(char)))))
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
