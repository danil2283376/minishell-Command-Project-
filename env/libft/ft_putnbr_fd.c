/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:31:59 by scolen            #+#    #+#             */
/*   Updated: 2020/11/06 20:56:53 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	input_reverse_array(char *arr, unsigned int len_nbr, int fd)
{
	while (len_nbr--)
	{
		ft_putchar_fd(arr[len_nbr], fd);
	}
}

static void	convert_to_string(int n, int fd)
{
	char			arr[11];
	long			nbr;
	unsigned int	start;

	nbr = n;
	start = 0;
	if (nbr < 0)
		nbr = nbr * (-1);
	while (nbr != 0)
	{
		arr[start] = (nbr % 10) + '0';
		nbr = nbr / 10;
		start++;
	}
	arr[start] = '\0';
	input_reverse_array(arr, start, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
		convert_to_string(n, fd);
}
