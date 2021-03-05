/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:34:17 by melisha           #+#    #+#             */
/*   Updated: 2021/02/25 17:22:30 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

size_t		ft_strlen(const char *str);
char		*ft_strcpy(char *dst, const char *src);
ssize_t		ft_write(int fildes, const void *buf, size_t nbyte);
ssize_t		ft_read(int fildes, void *buf, size_t nbyte);
char		*ft_strdup(const char *s1);
int			fn_space(char *line, int i);
int			ft_atoi(char *stc);
#endif
