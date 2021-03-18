/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:47:38 by melisha           #+#    #+#             */
/*   Updated: 2021/03/17 18:53:52 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libminishell.h"

void	output_list(t_list *list)
{
	t_list		*copy;
	char		*string;

	copy = list;
	string = NULL;
	while (copy->next != NULL)
	{
		copy = copy->next;
		string = (char *)(copy->content);
		write(1, string, ft_strlen(string));
		write(1, "\n", 1);
	}
}
