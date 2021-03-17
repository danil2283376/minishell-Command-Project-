/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:26:07 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 11:26:26 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		sum;
	int		val;

	i = 0;
	sum = 0;
	val = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
				str[i] == '\f' || str[i] == '\v' || str[i] == '\r' ||
				str[i] == '0'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			val = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + (str[i] - '0');
		i++;
	}
	return (sum * val);
}
