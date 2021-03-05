NAME = libasm.a
HEAD = libasm.h
OBJ = ft_strlen.o ft_strcpy.o ft_write.o ft_read.o ft_strdup.o fn_space.o ft_atoi.o
SRC = ft_strlen.s ft_strcpy.s ft_write.s ft_read.s ft_strdup.s fn_space.s ft_atoi.s
all: $(NAME)

$(NAME): $(HEAD) $(SRC)
	nasm -fmacho64 ft_strlen.s
	nasm -fmacho64 ft_strcpy.s
	nasm -fmacho64 ft_write.s
	nasm -fmacho64 ft_read.s
	nasm -fmacho64 ft_strdup.s
	nasm -fmacho64 fn_space.s
	nasm -fmacho64 ft_atoi.s
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean	all

.PHONY: all, clean, fclean, re
