/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:52:22 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 14:38:33 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

static int		ft_count(int n)
{
	int		count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char		*ft_fillarr(char *arr, int n, char j, int count)
{
	int		i;

	i = 0;
	if (n == 0)
		arr[i++] = n + '0';
	while (n)
	{
		if (j == '-' && n == 2147483647)
			arr[--count] = ((n % 10) + 1) + '0';
		else
			arr[--count] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	if (j == '-')
	{
		arr[count - 1] = '-';
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char			*ft_itoa(int n)
{
	char	*arr;
	int		i;
	int		count;
	char	j;

	j = '1';
	i = 0;
	count = ft_count(n);
	if (n < 0)
	{
		j = '-';
		if (n == -2147483648)
			n++;
		n = n * (-1);
	}
	if (!(arr = (char *)malloc((count + 1) * sizeof(char))))
		return (NULL);
	return (ft_fillarr(arr, n, j, count));
}
