/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 09:23:48 by melisha           #+#    #+#             */
/*   Updated: 2021/03/15 18:51:32 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int		get_next_line(char **line, int fd)
{
	int		i;
	char	*buf;
	int		j;

	i = 0;
	if (!(buf = (char *)malloc(sizeof(char) * 10000)))
		return (-1);
	while ((j = read(fd, &buf[i], 1)) > 0 && buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (j == 0 && i == 0)
		write(1, "exit", 4);
	buf[i] =  ' ';
	buf[i + 1] = ' ';
	buf[i + 2] = '\0';
	*line = buf;
	return (j);
}
