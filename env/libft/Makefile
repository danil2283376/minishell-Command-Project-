# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scolen <scolen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 17:56:57 by scolen            #+#    #+#              #
#    Updated: 2020/11/10 17:56:58 by scolen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = $(shell find . -name "ft_*.c")

OBJC = ${SRS:.c=.o}

NAME = libft.a

FLAG = -Wall -Wextra -Werror

OBJC = ${SRC:.c=.o}

GCC = gcc

.c.o:
	${GCC} ${FLAG} -I. -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	ar rc ${NAME} ${OBJC}

bonus: all

clean:
	rm -f ${OBJC}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
