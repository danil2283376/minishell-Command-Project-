/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:34:58 by melisha           #+#    #+#             */
/*   Updated: 2021/02/14 12:35:20 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	csize;

	csize = size * nmemb;
	if (!(arr = malloc(csize)))
		return (NULL);
	ft_bzero(arr, csize);
	return (arr);
}
