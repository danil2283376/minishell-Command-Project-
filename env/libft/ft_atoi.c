/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:01:31 by scolen            #+#    #+#             */
/*   Updated: 2020/11/12 10:46:59 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int					ft_check_minus(const char *s)
{
	unsigned int i;

	i = 0;
	while ((s[i] < '0' || s[i] > '9') && s[i] != '+' && s[i] != '-')
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		{
			i++;
			continue ;
		}
		else if (s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
		{
			i++;
			continue ;
		}
		else
			return (-1);
	}
	return (i);
}

static unsigned long long	ft_input_integer(const char *s, unsigned int l)
{
	unsigned int		start;
	unsigned long long	number;
	long long			discharge;

	start = 0;
	number = 0;
	discharge = 1;
	while (start++ < l)
		discharge = discharge * 10;
	discharge = discharge / 10;
	start = 0;
	while (start < l)
	{
		if (number <= 2147483648ULL)
		{
			number = ((s[start] - '0') * discharge) + number;
			discharge = discharge / 10;
		}
		start++;
	}
	return (number);
}

static long int				f(int s, char *str, unsigned int l)
{
	char				symbol;
	unsigned long long	n;

	n = 0;
	symbol = str[s];
	if (symbol == '-' || symbol == '+')
		s = s + 1;
	while (str[s] >= '0' && str[s] <= '9')
	{
		l++;
		s++;
	}
	s = s - l;
	n = (ft_input_integer(&str[s], l));
	if (n >= 9223372036854775807)
	{
		if (symbol == '-')
			return (0);
		else
			return (-1);
	}
	if (symbol == '-')
		return ((int)-n);
	return (n);
}

int							ft_atoi(const char *str)
{
	int				start;
	unsigned int	length_number;
	long long int	number;
	char			symbol;

	start = ft_check_minus(str);
	number = 0;
	length_number = 0;
	if (start < 0)
		return (0);
	symbol = str[start];
	number = f(start, (char *)str, length_number);
	return (number);
}
